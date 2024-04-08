#pragma once
#include <Arduino.h>

class Joystick {
    private:
        uint8_t VRX_pin;
        uint8_t VRY_pin;
        uint8_t swbtn_pin;
        bool swbtn;
        float VRX;
        float VRY;
    
    public:
        Joystick(uint8_t VRX_pin=-1, uint8_t VRY_pin=-1, uint8_t swbtn_pin=-1);
        
        void update_states();
        int read_vrx();
        int read_vry();
        bool read_sw();      
};