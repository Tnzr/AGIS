// WaterPump.h

#ifndef WaterPump_h
#define WaterPump_h

#include <Arduino.h>

class WaterPump {
  private:
    int pwm_pin;
    float lph;
    int State;
    
  public:
    WaterPump(int pwm_pin, float lph);
    void setPWM(float dcycle);
    int getState();
};

#endif WaterPump_h
