#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "SPIFFS.h"
#include "FS.h"

#include <Actuators.h>
#include <Sensors.h>
#include <Controllers.h>
#include <Algorithms.h>
#include <DHT_driver.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


#include <ArduinoJson.h>
#include <unordered_map>
#include <string>
#include "config.h"
// #include <IMU.h>

#define WATERPUMP_PIN 15
// #define DHT_PIN
#define LED 2
#define print(x)  Serial.print(x)


// PLEASE CHECK THE LIB DIRECTORY FOR PROGRESS
// The main binary will be developed once all necessary classes are defined
Config config;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

String header;
std::hash<std::string> hasher;

// DHT_driver dht;
// MPU6050 imu("MPU6050", 22);
unsigned long currentTime = millis();
unsigned long previousTime = 0;

unsigned long timerDelta = 5000;
const unsigned long timeoutTime = 2000;

void notifyClients(String sensorReadings) {
	ws.textAll(sensorReadings);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
	AwsFrameInfo *info = (AwsFrameInfo*)arg;
	if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
		data[len] = 0;
		String message = (char*) data;
		if(strcmp((char*)data, "getReadings")==0){
			String sensorReadings;// = dht.toJSON();
			print(sensorReadings);
			notifyClients(sensorReadings);
		}
	}
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initSPIFFS(){
	Serial.println(ESP.getFreeHeap());
	Serial.println(SPIFFS.begin(true));

	if (!SPIFFS.begin(true))
	{
		Serial.println("An Error has ocurred while mounting SPIFFS");
		return;
	}else{
		Serial.println("SPIFFS mounted successfully");
	}
}

void initWebSocket(AsyncWebSocket &socket, AsyncWebServer &server){
	socket.onEvent(onEvent);
	server.addHandler(&socket);
}

void initWiFi(){
	WiFi.mode(WIFI_STA);
	print("Connecting to Wifi .. ");
	print("Connecting to: ");
	// Serial.println(String(config.wifi.ssid));
	// Serial.println(hasher(config.wifi.ssid));
	// Serial.println(config.wifi.password);
	WiFi.begin(config.wifi.ssid, config.wifi.password);
	while (WiFi.status() != WL_CONNECTED) {
		print('.');
		digitalWrite(LED, HIGH);
		delay(1000);
		digitalWrite(LED, LOW);
		Serial.println(WiFi.localIP());
	}
	Serial.println("");
	Serial.println("WiFi connected.");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void blink(unsigned long time){
	digitalWrite(LED, HIGH);
	delay(time/2);
	digitalWrite(LED, LOW);
	delay(time/2);
}

void setup() {

	Serial.begin(115200);
	pinMode(LED, OUTPUT);
	Serial.println("Serial");
	initSPIFFS();
	Serial.println("initSPIFFS");
	config.loadConfig("/config.json");
	Serial.println("loaded config");
	      Serial.println(config.info.name);

      Serial.println(config.network.host);
      Serial.println(config.wifi.ssid);
      Serial.println(config.wifi.password);

	initWiFi(); // Turn On WiFi and Connect to known SSID
	Serial.println("wifi");
	server = AsyncWebServer(config.network.port);
	initWebSocket(ws, server);


	server.serveStatic("/", SPIFFS, "/");
	server.begin();
	// dht = DHT_driver(config.wiring.dhtPin);
}

 
void loop() {
	print("Connecting to: ");

	blink(100);
	Serial.println("sensor");

	if ((millis() - previousTime)> timerDelta){
		blink(100);
		String sensorReadings;// = dht.toJSON();
		// String imuReading = imu.toJSON();
		Serial.println(sensorReadings);
		// Serial.println(imuReading);
		// Serial.println("foidfb");
		// sensorReadings.concat(imuRseading);
		notifyClients(sensorReadings);
		previousTime = millis();
	}
	ws.cleanupClients();

}

