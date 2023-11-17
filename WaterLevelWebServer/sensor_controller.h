#ifndef SENSOR_CONTROLLER_H_
#define SENSOR_CONTROLLER_H_

volatile int water_level = 0;
volatile bool pump_status = false;

// Pin to control pump
const int pump_control_signal = 2;

// Ultrasonic sensor pin setup
const int TRIG_PIN=27;
const int ECHO_PIN=14;

const int BAUD_RATE=115200;

unsigned long duration;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
}

void Core2Task(void *parameters) {
  while(true){
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    water_level = duration/29/2;
    if(duration==0){
      Serial.println("Warning: no pulse from sensor");
    } 
    else{
        Serial.print("distance to nearest object:");
        Serial.println(distance);
        Serial.println(" cm");
    }
    delay(100);
  }
 }

#endif