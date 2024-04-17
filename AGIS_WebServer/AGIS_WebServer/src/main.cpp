#include <Arduino.h>
#include <WiFi.h>
#include <config.h>
// put function declarations here:

const char* ssid = SSID;
const char* password = PASSWORD;

WiFiServer server(80);
String header;
String sensor 

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}