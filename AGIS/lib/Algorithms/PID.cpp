#include <PID.h>
#include <algorithm>

PID::PID(double Kp, double Ki, double Kd, unsigned long dt, double min, double max)
    : Kp(Kp), Ki(Ki), Kd(Kd), min(min), max(max), deltaTime(dt ? dt : 1){
    reset();
}

void PID::reset(){
    E = dE = IntE = 0;
    hasPreviousError = false;
}

double PID::calc_ctrl(double state, double target, double elapsedSeconds){
    const double dt = elapsedSeconds > 0 ? elapsedSeconds : deltaTime / 1000.0;
    const double error = target - state;
    dE = hasPreviousError ? (error - E) / dt : 0;
    E = error;
    hasPreviousError = true;

    const double integral = IntE + error * dt;
    const double output = Kp * E + Ki * integral + Kd * dE;
    if ((output <= max || error < 0) && (output >= min || error > 0)){
        IntE = integral;
    }
    return std::max(min, std::min(max, output));
}
