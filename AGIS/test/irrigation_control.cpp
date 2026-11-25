#include <IrrigationControl.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <limits>

int main(){
    PID pid(0.2, 0.1, 0.2, 1000, -1, 1);
    assert(std::abs(pid.calc_ctrl(0, 1) - 0.3) < 1e-9);
    assert(std::abs(pid.calc_ctrl(0.5, 1) - 0.15) < 1e-9);
    assert(pid.calc_ctrl(-100, 1) == 1);
    pid.reset();
    assert(pid.calc_ctrl(1, 1) == 0);

    IrrigationControl control;
    const auto disabled = control.step(26, 50, 0, 0, 5);
    assert(disabled.pumpPwm == 0 && disabled.fanPwm == 0);

    const double target = 1.5;
    double flow = 0;
    for (int sample = 0; sample < 25; ++sample){
        const auto output = control.step(32, 50, flow, target, 5);
        if (sample == 0){
            assert(output.pumpPwm > 0);
        }
        assert(output.fanPwm == 102);
        if (sample % 6 == 0){
            std::printf("t=%3ds flow=%.2f L/min target=%.2f pump_pwm=%u fan_pwm=%u\n",
                        sample * 5, flow, target, unsigned(output.pumpPwm), unsigned(output.fanPwm));
        }
        flow += 0.35 * (3.0 * output.pumpPwm / 255 - flow);
    }
    assert(std::abs(flow - target) < 0.05);

    IrrigationControl fastControl;
    double fastFlow = 0;
    for (int sample = 0; sample < 25; ++sample){
        const auto output = fastControl.step(32, 50, fastFlow, target, 5);
        fastFlow = 3.0 * output.pumpPwm / 255;
        if (sample >= 20){
            std::printf("Fast plant t=%3ds flow=%.2f L/min target=%.2f pump_pwm=%u\n",
                        sample * 5, fastFlow, target, unsigned(output.pumpPwm));
        }
    }
    assert(std::abs(fastFlow - target) < 0.05);

    const auto highFlow = control.step(27, 70, 4, target, 5);
    assert(highFlow.pumpPwm == 0 && highFlow.fanPwm > 102);
    const double invalid = std::numeric_limits<double>::quiet_NaN();
    const auto invalidReadings = control.step(invalid, invalid, invalid, target, 5);
    assert(invalidReadings.pumpPwm == 0 && invalidReadings.fanPwm == 0);
    std::puts("PASS: PID math, simulated flow convergence, fan response and disabled/invalid inputs");
}
