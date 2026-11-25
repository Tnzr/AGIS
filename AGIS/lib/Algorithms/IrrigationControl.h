#pragma once
#include <PID.h>
#include <stdint.h>

struct IrrigationOutput {
    uint8_t pumpPwm;
    uint8_t fanPwm;
};

class IrrigationControl {
    PID pump{0.25, 0.04, 0, 5000, 0, 1};
    PID temperatureFan{0.1, 0, 0, 5000, 0, 1};
    PID humidityFan{0.05, 0, 0, 5000, 0, 1};

public:
    IrrigationOutput step(double temperature, double humidity, double flowLitresPerMinute,
                          double targetFlowLitresPerMinute, double elapsedSeconds);
};
