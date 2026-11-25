#include <IrrigationControl.h>
#include <algorithm>
#include <cmath>

IrrigationOutput IrrigationControl::step(double temperature, double humidity, double flowLitresPerMinute,
                                        double targetFlowLitresPerMinute, double elapsedSeconds){
    double pumpDuty = 0;
    if (std::isfinite(targetFlowLitresPerMinute) && targetFlowLitresPerMinute > 0 &&
        std::isfinite(flowLitresPerMinute) && flowLitresPerMinute >= 0){
        pumpDuty = pump.calc_ctrl(flowLitresPerMinute / targetFlowLitresPerMinute, 1, elapsedSeconds);
    } else {
        pump.reset();
    }

    const double heatDuty = std::isfinite(temperature) ? temperatureFan.calc_ctrl(28, temperature, elapsedSeconds) : 0;
    const double humidityDuty = std::isfinite(humidity) ? humidityFan.calc_ctrl(55, humidity, elapsedSeconds) : 0;
    return {static_cast<uint8_t>(std::lround(pumpDuty * 255)),
            static_cast<uint8_t>(std::lround(std::max(heatDuty, humidityDuty) * 255))};
}
