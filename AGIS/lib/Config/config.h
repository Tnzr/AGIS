#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include "FS.h"
#include "SPIFFS.h"
// Define the maximum size of the JSON buffer based on your configuration size
#define JSON_CONFIG_SIZE 1024

struct NetworkConfig {
  String host;
  uint16_t port = 8080;
};

struct WifiConfig {
  String ssid;
  String password;
};

struct WiringConfig {
  uint8_t dhtPin = 4;
  uint8_t waterflowPin = 18;
};

struct SystemInfo {
String name;
String version;
bool debug;
};

struct AppConfig {
  SystemInfo info;
  NetworkConfig network;
  WifiConfig wifi;
  WiringConfig wiring;
};

class Config {

  public:
    SystemInfo info;
    NetworkConfig network;
    WifiConfig wifi;
    WiringConfig wiring;
    float targetFlowLpm = 0;
    void loadConfig(String filename);
};


void Config::loadConfig(String filename){
      File configFile = SPIFFS.open(filename, "r");

      if (!configFile) {
        Serial.println("Failed to open config file");
        return;
      }

      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, configFile);
      configFile.close();
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }
      info.name = doc["name"].as<String>();
      Serial.println(info.name);
      info.version = doc["version"].as<String>();
      info.debug = doc["debug"].as<bool>();

      // Network config
      network.host = doc["network"]["host"].as<String>();
      network.port = doc["network"]["port"] | network.port;
      Serial.println(network.host);

      // Wifi config
      wifi.ssid = doc["wifi"]["ssid"].as<String>();
      wifi.password = doc["wifi"]["password"].as<String>();

      // Wiring config
      wiring.dhtPin = doc["wiring"]["dht_pin"][0] | wiring.dhtPin;
      wiring.waterflowPin = doc["wiring"]["waterflow_pin"][0] | wiring.waterflowPin;
      targetFlowLpm = doc["irrigation"]["target_flow_lpm"] | 0.0f;

    }
