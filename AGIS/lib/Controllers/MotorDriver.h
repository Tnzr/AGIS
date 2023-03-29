#pragma once
#include <Arduino.h>

class MotorDriver{
    private:
        uint8_t enable_pin; // PWM
        uint8_t inA_pin; // BOOL for polarity
        uint8_t inB_pin; // ALWAYS !inA_pin or BOTH LOW
        float speed; // -1 <-> 1
        bool polarity; // FALSE natural state


    public:
        MotorDriver(unsigned int enable_pin, unsigned short int inA_pin, unsigned short inB_pin, bool polarity = true);
        bool getPolarity();
        void setPolarity(bool new_polarity);
        void setPWM(unsigned short int dcycle);
        void setSpeed(float speed);

};