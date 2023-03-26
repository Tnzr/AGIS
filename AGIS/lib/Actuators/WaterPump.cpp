//WaterPump cpp

#include "WaterPump.h"

WaterPump::WaterPump(int pwm_pin, float lph){
  this.pwm_pin = pwm_pin;
  this.lph = lph;
  
  pinMode(this.pwm_pin, OUTPUT);
  }

WaterPump::setPWM(float dcycle){
  analogWrite(this.pwm_pin, int(dcycle*255));
  }

WaterPump::getState(){
  return this.State;
  }
