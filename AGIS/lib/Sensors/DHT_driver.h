#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <Sensors.h>
// Temperature and Humidity Sensor

typedef struct DHT_Measurement{
    float temperature;
    float humidity;
} DHT_Measurement; 



class DHT_driver {
    private:
        DHT dht;
        uint8_t data_pin;
        DHT_Measurement stats;
        JsonObject appendDatatoJson(SensorData data, JsonArray &sensorArray);

    public:
        String id;
        
        DHT_driver(uint8_t data_pin = 4);
        float getHumidity();
        float getTemperature();
        DHT_Measurement sampleRead();
        String toJSON();
        void setSensorName(String name);

};


