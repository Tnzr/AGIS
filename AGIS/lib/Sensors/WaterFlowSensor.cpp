// WaterFlowSensor cpp

#include "WaterFlowSensor.h"

WaterFlowSensor::WaterFlowSensor(int sense_pin, float conversion){
    this.sensor_pin = sense_pin;
    this.tick_to_volume = conversion;
    attachInterrupt(digitalPinToInterrupt(this.sensor_pin), this.increase, RISING);
  }

WaterFlowSensor::increase(){
  this.pulse_count++;
  }
