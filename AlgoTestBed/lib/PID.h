#pragma once

class PID{
    private:
        double Kp;
        double Ki;
        double Kd;
        double E;
        double dE;
        double IntE;
        double ctrl_vr;
        double target;
        double state;
        double min, max;
        unsigned long deltaTime;
        unsigned long lastUpdate;
        
        template<typename T> T limit(T input, T min, T max);
        void updateError(double error);
        

    public:
        PID(double Kp = 1, double Ki = 1, double Kd = 1, unsigned long dt = 1, double min = -1, double max = 1);
        ~PID();
        double calc_ctrl(double state, double target=55);
};