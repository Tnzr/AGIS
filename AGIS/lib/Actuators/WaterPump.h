// WaterPump.h

#pragma once
#include <Arduino.h>

class WaterPump {
  private:
    uint8_t pwm_pin;
    uint8_t State;
    float lph;
    
    
  public:
    WaterPump(uint8_t pwm_pin, float lph);
    void setPWM(float dcycle);
    int getState();
};
