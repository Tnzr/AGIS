// WaterPump.h

#pragma once
#include <Arduino.h>

typedef struct WaterPump_Stat{
  float dutyCycle;
  uint8_t state;

}WaterPump_Stat;


class WaterPump {
  private:
    uint8_t pwm_pin; // PWM Signal Pin
    uint8_t State;  //  Check if Operating with Flow Rate Sensor
    float lph; // liters per hour
    float duty_cycle;
    
  public:
    WaterPump(uint8_t pwm_pin, float lph);
    void setPWM(float dcycle);
    int getState();
};
