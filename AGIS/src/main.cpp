#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <atomic>
#include <cstring>
#include <DHT_driver.h>
#include <IrrigationControl.h>
#include <WaterFlowSensor.h>
#include "config.h"

constexpr uint8_t pumpPin = 5;
constexpr uint8_t fanPin = 14;
constexpr uint8_t fanSupplyPin = 12;
constexpr uint8_t pumpChannel = 0;
constexpr uint8_t fanChannel = 2;
constexpr unsigned long sampleIntervalMs = 5000;

Config config;
AsyncWebSocket ws("/ws");
std::atomic<bool> readingsRequested{false};
IrrigationControl control;

void onEvent(AsyncWebSocket *, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected\n", client->id());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA: {
            const auto *info = static_cast<const AwsFrameInfo *>(arg);
            constexpr char command[] = "getReadings";
            if (info->final && info->index == 0 && info->len == len &&
                info->opcode == WS_TEXT && len == sizeof(command) - 1 &&
                std::memcmp(data, command, len) == 0) {
                readingsRequested.store(true);
            }
            break;
        }
        default:
            break;
    }
}

void setup() {
    Serial.begin(115200);

    ledcSetup(pumpChannel, 1000, 8);
    ledcSetup(fanChannel, 25000, 8);
    ledcAttachPin(pumpPin, pumpChannel);
    ledcAttachPin(fanPin, fanChannel);
    ledcWrite(pumpChannel, 0);
    ledcWrite(fanChannel, 0);
    pinMode(fanSupplyPin, OUTPUT);
    digitalWrite(fanSupplyPin, HIGH);

    const bool mounted = SPIFFS.begin(true);
    if (mounted) {
        config.loadConfig("/config.json");
    } else {
        Serial.println("Failed to mount SPIFFS");
    }

    WiFi.mode(WIFI_STA);
    if (config.wifi.ssid.length()) {
        WiFi.begin(config.wifi.ssid.c_str(), config.wifi.password.c_str());
    }

    static AsyncWebServer server(config.network.port);
    ws.onEvent(onEvent);
    server.addHandler(&ws);
    if (mounted) {
        server.serveStatic("/", SPIFFS, "/");
    }
    server.begin();
}

void loop() {
    static DHT_driver dht(config.wiring.dhtPin);
    static WaterFlowSensor waterFlow(config.wiring.waterflowPin);
    static unsigned long lastSample = millis();
    static String telemetry;

    const unsigned long now = millis();
    const unsigned long elapsed = now - lastSample;
    const bool requested = readingsRequested.exchange(false);
    if (elapsed >= sampleIntervalMs) {
        lastSample = now;
        const float flowLpm = waterFlow.sampleLitresPerMinute(now);
        const DHT_Measurement reading = dht.sampleRead();
        const auto output = control.step(reading.temperature, reading.humidity, flowLpm,
                                         config.targetFlowLpm, elapsed / 1000.0);
        ledcWrite(pumpChannel, output.pumpPwm);
        ledcWrite(fanChannel, output.fanPwm);

        JsonDocument doc;
        dht.appendReadings(doc, reading);
        doc["Waterflow_Sensor"]["flow_lpm"] = flowLpm;
        doc["Waterflow_Sensor"]["target_lpm"] = config.targetFlowLpm;
        doc["Actuators"]["pump_pwm"] = output.pumpPwm;
        doc["Actuators"]["fan_pwm"] = output.fanPwm;
        telemetry = "";
        serializeJson(doc, telemetry);
        Serial.println(telemetry);
        ws.textAll(telemetry);
    } else if (requested && telemetry.length()) {
        ws.textAll(telemetry);
    }

    ws.cleanupClients();
    delay(20);
}
