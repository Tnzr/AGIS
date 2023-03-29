
#pragma once
#include <Arduino.h>

class Fan{
    private:
        unsigned short int driving_pin;
        unsigned short int sensor_pin;
        unsigned short int max_rpm;
        unsigned short int cfm;

    public:
        Fan();
};

