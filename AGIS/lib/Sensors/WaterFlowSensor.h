// WaterPump.h

#pragma once
#include <Arduino.h>

class WaterFlowSensor{
  
  private:
    uint8_t sensor_pin;
    float tickToVolume; // ie. ticks to mL
    float flowRate; // Current V / t
    float currentVolume;
    volatile unsigned short int tick_count; // 
    unsigned long lastUpdate; // time of last update
    unsigned long deltaTime; // differance in millis
    unsigned long now; 
    float updateDelta;
    void *pulse_tick();
    void updateFlowRate();

  public:
    WaterFlowSensor(int sense_pin, float conversion, unsigned long updateDelta);
    void resetVolume();
    float getVolume();
    // static void _attachInterrupt(uint8_t pin, void *callback, int mode);
  };