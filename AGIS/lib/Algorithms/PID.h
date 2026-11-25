#pragma once

class PID{
    private:
        double Kp;
        double Ki;
        double Kd;
        double E;
        double dE;
        double IntE;
        double min, max;
        unsigned long deltaTime;
        bool hasPreviousError;
        

    public:
        PID(double Kp = 1, double Ki = 1, double Kd = 1, unsigned long dt = 1, double min = -1, double max = 1);
        double calc_ctrl(double state, double target=55, double elapsedSeconds=0);
        void reset();
};