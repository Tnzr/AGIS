
#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Sensors.h>
typedef struct FanStatus {
    float currentRPM;
    unsigned short int cfm; 
} FanStatus;


class Fan{
    private:
        uint8_t driving_pin;
        uint8_t sensor_pin;
        FanStatus status;
        unsigned long deltaTime; // in millis
        float currentRPM; // rev / min
        unsigned long updateDelta; // in millis
        unsigned long now; // current milli time
        float tpr; //ticks per revolution
        unsigned short int maxRPM; // max rpm to compute best
        unsigned short int cfm; // cubic feet / min
        volatile unsigned short int tickCount; // pulse count
        unsigned long lastUpdate; // last time of update
        void *rev_tick();
        void updateTickFrequency();
        JsonObject appendDatatoJson(SensorData data, JsonArray &sensorArray);


    public:
        Fan(uint8_t driving_pin, uint8_t sensor_pin, 
            unsigned short int max_rpm, unsigned short int cfm, 
            unsigned long updateDelta = 0);
        unsigned short int getRPM();
        void setPWM(float dcycle); 
        String toJSON();

};

