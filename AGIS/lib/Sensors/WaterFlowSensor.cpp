// WaterFlowSensor cpp

#include "WaterFlowSensor.h"


WaterFlowSensor::WaterFlowSensor(int sense_pin, float conversion){
    this->sensor_pin = sense_pin;
    this->tick_to_volume = conversion;
    this->pulse_count = 0;
    attachInterrupt(digitalPinToInterrupt(this->sensor_pin), (void(*)())this->pulse_tick(), RISING);
  }

// static void _attachInterrupt(uint8_t pin, void *callback, int mode){
//   attachInterrupt(digitalPinToInterrupt(pin), (void(*)())callback, mode);
// }

void *WaterFlowSensor::pulse_tick(){
  this->pulse_count++;
}

float WaterFlowSensor::getVolume(){
  return this->pulse_count*tick_to_volume;
}

