#include "WaterFlowSensor.h"

constexpr float pulsesPerLitre = 450.0f;

WaterFlowSensor::WaterFlowSensor(uint8_t pin) : lastSample(millis()){
    pinMode(pin, INPUT);
    attachInterruptArg(digitalPinToInterrupt(pin), pulseTick, this, RISING);
}

void IRAM_ATTR WaterFlowSensor::pulseTick(void *arg){
    auto &sensor = *static_cast<WaterFlowSensor *>(arg);
    portENTER_CRITICAL_ISR(&sensor.lock);
    ++sensor.pulses;
    portEXIT_CRITICAL_ISR(&sensor.lock);
}

float WaterFlowSensor::sampleLitresPerMinute(unsigned long now){
    const unsigned long elapsed = now - lastSample;
    if (!elapsed) {
        return 0;
    }

    portENTER_CRITICAL(&lock);
    const uint32_t count = pulses;
    pulses = 0;
    portEXIT_CRITICAL(&lock);
    lastSample = now;
    return count * 60000.0f / (pulsesPerLitre * elapsed);
}
