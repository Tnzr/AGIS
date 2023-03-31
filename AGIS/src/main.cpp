#include <Arduino.h>

#include <Actuators.h>
#include <Sensors.h>

#define WATERPUMP_PIN 15
#define IWFSENSOR_PIN 2

/// PLEASE CHECK THE LIB DIRECTORY FOR PROGRESS
// The main binary will be developed once all necessary classes are defined

void setup() {
  // put your setup code here, to run once:
  WaterFlowSensor wfsensor = WaterFlowSensor(IWFSENSOR_PIN, 2.5);
  WaterPump waterPump = WaterPump(WATERPUMP_PIN, 300);

}

void loop() {
  // put your main code here, to run repeatedly:
  
}