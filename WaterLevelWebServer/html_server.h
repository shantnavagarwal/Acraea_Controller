#include <string>
#ifndef HTML_SERVER_H_
#define HTML_SERVER_H_

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>
#include "sensor_controller.h"

#define WIFI_SSID "ESP32"
#define WIFI_PASSWORD "OpenHardware"
#define WIFI_CHANNEL 40

WebServer server(80);

void sendHtml() {
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
          <h2>Water Level: WATER_LEVEL_INP cm</h2>
          <h2>Pump Status: PUMP_STATUS_INP</h2>
        </div>
      </body>
    </html>
  )";
// <a href="/toggle/2" class="btn LED2_TEXT">LED2_TEXT</a>
  response.replace("WATER_LEVEL_INP", std::string(water_level));
  response.replace("PUMP_STATUS_INP", pump_status ? "ON" : "OFF");
  server.send(200, "text/html", response);
}

void setup(void) {
  Serial.begin(115200);

  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Setting up WiFi ");
  Serial.print(WIFI_SSID);

  Serial.println(" Connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", sendHtml);

    sendHtml();
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);
}

#endif