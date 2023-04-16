#include <Joystick.h>


Joystick::Joystick(uint8_t VRX_pin, uint8_t VRY_pin, uint8_t swbtn_pin){
    this->VRX_pin = VRX_pin;
    this->VRY_pin = VRY_pin;
    this->swbtn_pin = swbtn_pin;

    pinMode(this->VRX_pin, INPUT);
    pinMode(this->VRY_pin, INPUT);
    pinMode(this->swbtn_pin, INPUT);


}

void Joystick::update_states(){
    this->VRX = analogRead(this->VRX_pin);
    this->VRY = analogRead(this->VRY_pin);
    this->swbtn = digitalRead(this->swbtn_pin);    
}
