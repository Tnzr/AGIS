#pragma once
#include <Arduino.h>

class WaterFlowSensor {
    portMUX_TYPE lock = portMUX_INITIALIZER_UNLOCKED;
    volatile uint32_t pulses = 0;
    unsigned long lastSample;
    static void IRAM_ATTR pulseTick(void *arg);

public:
    explicit WaterFlowSensor(uint8_t pin);
    float sampleLitresPerMinute(unsigned long now);
};
