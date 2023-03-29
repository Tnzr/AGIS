// WaterPump.h

#pragma once
#include <Arduino.h>

class WaterFlowSensor{
  
  private:
    unsigned int sensor_pin;
    float tick_to_volume;
    volatile long pulse_count;
    void *pulse_tick();

  public:
    WaterFlowSensor(int sense_pin, float conversion);
    // static void _attachInterrupt(uint8_t pin, void *callback, int mode);
    float getVolume();
  };