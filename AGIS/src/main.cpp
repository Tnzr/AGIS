#include <Arduino.h>
#include <Actuators.h>
#include <Sensors.h>
#include <Controllers.h>
#include <Algorithms.h>
#include <DHT_driver.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <unordered_map>
#include <string>
#include "system_config.h"
// #include <FTBDLL.cpp>
#define WATERPUMP_PIN 15
#define IWFSENSOR_PIN 2
// #define DHT_PIN
#define LED 2
#define print(x)  Serial.print(x)

// PLEASE CHECK THE LIB DIRECTORY FOR PROGRESS
// The main binary will be developed once all necessary classes are defined

AsyncWebServer server(Config::Network::PORT);
AsyncWebSocket ws("/ws");

String header;
std::hash<std::string> hasher;

DHT_driver dht(Config::Wiring::DHT_PIN);
unsigned long currentTime = millis();
unsigned long previousTime = 0;

unsigned long timerDelta = 5000;
const unsigned long timeoutTime = 2000;

void initWiFi(){
	WiFi.mode(WIFI_STA);
	print("Connecting to Wifi .. ");
	print("Connecting to: ");
	Serial.println(hasher(Config::Wifi::SSID));
	WiFi.begin(Config::Wifi::SSID, Config::Wifi::PASSWORD);
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

void initSPIFFS(){
	if (!SPIFFS.begin(true))
	{
		Serial.println("An Error has ocurred while mounting SPIFFS");
	}
	Serial.println("SPIFFS mounted successfully");
}

void notifyClients(String sensorReadings) {
	ws.textAll(sensorReadings);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
	AwsFrameInfo *info = (AwsFrameInfo*)arg;
	if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
		data[len] = 0;
		String message = (char*) data;
		if(strcmp((char*)data, "getReadings")==0){
			String sensorReadings = dht.toJSON();
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

void initWebSocket(AsyncWebSocket &socket, AsyncWebServer &server){
	socket.onEvent(onEvent);
	server.addHandler(&socket);
}

void loadConfig(){
	File configFile = SPIFFS.open("/data/config.json", "r");
	if (!configFile) {
		Serial.println("Failed to open config file");
		return;
	}

	size_t size = configFile.size();
	std::unique_ptr<char[]> buf(new char[size]);
	configFile.readBytes(buf.get(), size);

	JsonDocument doc;
    DeserializationError error = deserializeJson(doc, buf.get());
    if (error) {
        Serial.println("Failed to parse config file");
        return;
    }
}

void setup() {

	Serial.begin(9600);
	pinMode(LED, OUTPUT);
	initWiFi(); // Turn On WiFi and Connect to known SSID
	initSPIFFS();
	initWebSocket(ws, server);

	server.serveStatic("/", SPIFFS, "/");
	server.begin();

	Serial.println("Setup Complete.");

}

void blink(unsigned long time){
	digitalWrite(LED, HIGH);
	delay(time/2);
	digitalWrite(LED, LOW);
	delay(time/2);
}

void loop() {

	blink(1000);
	
	if ((millis() - previousTime)> timerDelta){
		String sensorReadings = dht.toJSON();
		Serial.println(sensorReadings);
		notifyClients(sensorReadings);
		previousTime = millis();
	}
	ws.cleanupClients();

}

