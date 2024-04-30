#pragma once

#include <ArduinoJson.h>
#include "FS.h"
#include "SPIFFS.h"
// Define the maximum size of the JSON buffer based on your configuration size
#define JSON_CONFIG_SIZE 1024

struct NetworkConfig {
  String host;
  int port;
};

struct WifiConfig {
  const char* ssid;
  const char* password;
};

struct WiringConfig {
  uint8_t dhtPin;
  uint8_t waterflowPin;
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
    // Config();
    void loadConfig(String filename);
};


void Config::loadConfig(String filename){
      File configFile = SPIFFS.open(filename, "r");

      if (!configFile) {
        Serial.println("Failed to open config file");
        return;
      }

      size_t size = configFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      configFile.readBytes(buf.get(), size);
      configFile.close();

      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, buf.get());
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
      network.port = doc["network"]["port"].as<int>();
      Serial.println(network.host);

      // Wifi config
      wifi.ssid = doc["wifi"]["ssid"].as<const char*>();
      wifi.password = doc["wifi"]["password"].as<const char*>();
      Serial.println(wifi.ssid);
      Serial.println(wifi.password);

      // Wiring config
      wiring.dhtPin = doc["wiring"]["dht_pin"][0].as<int>();
      wiring.waterflowPin = doc["wiring"]["waterflow_pin"][0].as<int>();

    }

