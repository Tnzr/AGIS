#include <PID.h>

PID::PID(double Kp, double Ki, double Kd, unsigned long dt, double min, double max){
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->E = this->dE = this->IntE = 0;
    this->ctrl_vr = 0;
    this->target = 0;
    this->state = 0;
    this->lastUpdate = 0;
    this->deltaTime = 0;
    this->deltaTime = dt;
    this->min = min;
    this->max = max;
}

double PID::calc_ctrl(double state, double target){
    this->ctrl_vr = this->E*this->Kp + this->IntE*this->Ki + this->dE*this->Kd;
    return this->ctrl_vr;
}



template<typename T> T PID::limit(T input, T min, T max){
    if (input < min)
    {
        return min;
    }else if(input > max){
        return max;
    }else{
        return input;
    }
}

void PID::updateError(double error){
    this->deltaTime = millis() - this->lastUpdate;
    this->dE = (error - this->E)/this->deltaTime;
    this->E = error;
    this->IntE = this->E*this->deltaTime;

    


}

