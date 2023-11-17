#include <string>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>
#include "esp_random.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <AsyncTCP.h>
#include "ESPAsyncWebSrv.h"
#include "esp_system.h"

// Shared Memory
volatile int water_level = 0; // In centimeter
volatile bool mode_automatic = true;
volatile bool pump_status = false;
volatile bool target_water_level = 0;

// Define a semaphore for synchronization
SemaphoreHandle_t xSemaphore;

// Pin to control pump
const int pump_control_signal = 2;

// Comunication Setup
const int BAUD_RATE = 115200;

#define WIFI_SSID "ESP32"
#define WIFI_PASSWORD "OpenHardware"
#define WIFI_CHANNEL 40

AsyncWebServer server(80);

// Ultrasonic sensor setup
const int TRIG_PIN = 27;
const int ECHO_PIN = 14;
unsigned long duration = 0;
int distance_ultrasonic = 0; // In Centimeter
const int TimeDelay = 500; // milliseconds -> 500 == 2 Hz
const int container_depth = 20; // In centimeter

void sendHtml(AsyncWebServerRequest *request) {
  Serial.println("Webpage Served");
  String response = R"(
    <!DOCTYPE html><html>
      <head>
        <title>Acraea - Control Interface</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta http-equiv="refresh" content="1">
        <style>
          html { font-family: sans-serif; text-align: center; }
          body { display: inline-flex; flex-direction: column; }
          h1 { margin-bottom: 1.2em; } 
          h2 { margin: 0; }
          div { display: grid; grid-template-columns: 1fr 1fr; grid-template-rows: auto auto; grid-auto-flow: column; grid-gap: 1em; }
          .btn { background-color: #5B5; border: none; color: #fff; padding: 0.5em 1em;
                 font-size: 2em; text-decoration: none }
          .btn.OFF { background-color: #333; }
        </style>
      </head>
            
      <body>
        <h1>Acraea Control Interface</h1>
        <div>
          <h3>Water Level: WATER_LEVEL_INP cm</h2>
          <h3>Pump Status: PUMP_STATUS_INP</h2>
          <a href="/toggle/pump_mode" class="btn pump_mode">Switch to PUMP_MODE_INP mode</a>
          PUMP_MODE_SPECIFIC
        </div>
      </body>
    </html>
  )";
  String response_mode_automatic = R"(
<form action="/mode_automatic_form" method="get">
        <h3>Desired Water Level: DESIRED_WATER_LEVEL cm </h3>
        <label for="integerInput">Desired water level (cm):</label>
        <input type="number" id="integerInput" name="integerInput" required>
        <button type="submit">Submit</button>
    </form>
  )";
  String response_mode_manual = R"(
<a href="/toggle/pump_status" class="btn switch_pump">Switch pump PUMP_STATUS</a>
  )";
// <a href="/toggle/2" class="btn LED2_TEXT">LED2_TEXT</a>
  if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
    // Access and modify the shared variable
    response.replace("WATER_LEVEL_INP", String(water_level));
    response.replace("PUMP_STATUS_INP", pump_status ? "ON" : "OFF");
    response.replace("PUMP_MODE_INP", mode_automatic ? "Manual" : "Automatic");
    if (mode_automatic){
      response_mode_automatic.replace("DESIRED_WATER_LEVEL",String(target_water_level));
      response.replace("PUMP_MODE_SPECIFIC", response_mode_automatic);
    }
    else {
      response_mode_manual.replace("PUMP_STATUS", pump_status ? "OFF" : "ON");
      response.replace("PUMP_MODE_SPECIFIC", response_mode_manual);
    }
    // Release the semaphore
    xSemaphoreGive(xSemaphore);
  }
  Serial.println("Core " + String(1) + ": Accessed");
  request->send(200, "text/html", response);
}

void changePumpMode(AsyncWebServerRequest *request){
  if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
    // Access and modify the shared variable
    mode_automatic = !mode_automatic;
    target_water_level = 0;
    // Release the semaphore
    xSemaphoreGive(xSemaphore);
  }
  sendHtml(request);
}

void changePumpStatus(AsyncWebServerRequest *request){
  if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
    // Access and modify the shared variable
    pump_status = !pump_status;
    // Release the semaphore
    xSemaphoreGive(xSemaphore);
  }
  sendHtml(request);
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setWaterLevel(AsyncWebServerRequest *request){
    if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
      // Access and modify the shared variable
      mode_automatic = !mode_automatic;
      target_water_level = request->getParam("integerInput")->value().toInt();
      // Release the semaphore
      xSemaphoreGive(xSemaphore);
    }
    sendHtml(request);
  }

void core1Task(void *parameters){
  server.on("/", HTTP_GET, sendHtml);
  server.on("/toggle/pump_mode", HTTP_GET, changePumpMode);
  server.on("/mode_automatic_form", HTTP_GET, setWaterLevel);
  server.on("/toggle/pump_status", HTTP_GET, changePumpMode);
  server.onNotFound(notFound);
  server.begin();
  Serial.println("HTTP server started");

  while(true) {
    // server.handleClient();
    // delay(2);
  }
}

void sense_ultrasonic(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
  distance_ultrasonic = duration/29/2;
}

void control_algorithm(){
  if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
    // Access and modify the shared variable
    water_level = max(container_depth - distance_ultrasonic, 0);
    if (mode_automatic){
      pump_status = water_level < target_water_level ? true : false;
    }
    digitalWrite(pump_control_signal, pump_status ? 255 : 0);
    // Release the semaphore
    xSemaphoreGive(xSemaphore);
  }
  Serial.println("Core " + String(2) + ": " + String(water_level) + " Distance detected:" + String(distance_ultrasonic));
}

void core2Task(void *parameters){
  while (true){
    sense_ultrasonic();
    control_algorithm();
    delay(TimeDelay);
  }
}

void setup(void) {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(pump_control_signal, OUTPUT);

  xSemaphore = xSemaphoreCreateMutex();

  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Setting up WiFi ");
  Serial.print(WIFI_SSID);

  Serial.println(" Connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

    xTaskCreatePinnedToCore(
    core1Task,  // Task function
    "Core 1 Task",  // Task name
    10000,  // Stack size
    NULL,  // Task parameters
    1,  // Priority
    NULL,  // Task handle
    0);  // Core to run the task on (Core 0)

  xTaskCreatePinnedToCore(
    core2Task,  // Task function
    "Core 2 Task",  // Task name
    10000,  // Stack size
    NULL,  // Task parameters
    1,  // Priority
    NULL,  // Task handle
    1);  // Core to run the task on (Core 1)
}

void loop(void) {

}
