//WaterPump cpp

#include "WaterPump.h"

WaterPump::WaterPump(uint8_t pwm_pin, float lph){
  this->pwm_pin = pwm_pin;
  this->lph = lph;
  
  pinMode(this->pwm_pin, OUTPUT);
  }

void WaterPump::setPWM(float dcycle){
  analogWrite(this->pwm_pin, int(dcycle*255));
  }

int WaterPump::getState(){
  // 0 OK
  // -1 ERROR
  return this->State;
  }

