// WaterFlowSensor cpp

#include "WaterFlowSensor.h"


WaterFlowSensor::WaterFlowSensor(int sense_pin, float conversion){
    this->sensor_pin = sense_pin;
    this->tickToVolume = conversion;
    this->tick_count = 0;
    pinMode(sensor_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(this->sensor_pin), (void(*)())this->pulse_tick(), RISING);
  }

// static void _attachInterrupt(uint8_t pin, void *callback, int mode){
//   attachInterrupt(digitalPinToInterrupt(pin), (void(*)())callback, mode);
// }

void *WaterFlowSensor::pulse_tick(){
  this->now = millis();
  this->tick_count++;
  this->delta = this->now-this->lastUpdate;

  if (this->delta >= this->updateDelta){
    this->updateFlowRate();
    this->lastUpdate = this->now;
  }
  return nullptr;
}


void WaterFlowSensor::updateFlowRate(){
  // pulse * V/pulse * 1,000ms/s / delta (ms)
  this->flowRate = this->tick_count * this->tickToVolume * 1000 / this->delta;
  this->tick_count = 0;
}

float WaterFlowSensor::getVolume(){
  return this->currentVolume;
}

void WaterFlowSensor::resetVolume(){
  this->currentVolume = 0;
}

