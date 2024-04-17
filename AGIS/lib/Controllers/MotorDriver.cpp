#include <MotorDriver.h>

MotorDriver::MotorDriver(unsigned int enable_pin, unsigned short int inA_pin, unsigned short inB_pin, bool polarity){
    this->enable_pin = enable_pin;
    this->inA_pin = inA_pin;
    this->inB_pin = inB_pin;
    this->polarity = polarity;
    this->speed = 0;
    pinMode(this->enable_pin, OUTPUT); // ALL pins are Outputs
    pinMode(this->inA_pin, OUTPUT);
    pinMode(this->inB_pin, OUTPUT);
}

void MotorDriver::setPolarity(bool new_polarity){
    if(this->polarity != new_polarity){ // only change polarity if it needs to be changed
        this->polarity = new_polarity; // set to new polarity
        analogWrite(this->enable_pin, 0); // Turn the motor and H-bridge OFF to re-circuit safely
        digitalWrite(this->inA_pin, LOW);
        digitalWrite(this->inB_pin, LOW);
        
        digitalWrite(this->inA_pin, this->polarity); // Set A to polarity value and B to opposite
        digitalWrite(this->inB_pin, !this->polarity);
    }
}

bool MotorDriver::getPolarity(){
    return polarity;
}

void MotorDriver::setPWM(unsigned short int dcycle){
    // multiply duty cycle % by 255 and write to the enable pin
    analogWrite(this->enable_pin, int(dcycle*255));
}

void MotorDriver::setSpeed(float speed){
    setPolarity(speed < 0); // derive polarity from sign
    setPWM(abs(speed)); // dutycycle == speed
    this->speed = speed;
}

