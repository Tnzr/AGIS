#pragma once
#include <Arduino.h>
#include <stdio.h>
template <typename dType, typename tType> 
class SensorReading{
    private:
        dType reading;
        tType time;
    
    
    public:
        SensorReading(dType reading, tType t);
        SensorReading();
        ~SensorReading();
        
        void update_reading(dType reading, tType t);
        operator String() const {
        return "[" + String(this->reading) + ","+ String(this->time) + "]";
        };
};

template<typename dType, typename tType>
SensorReading<dType, tType>::SensorReading(dType reading, tType time){
    this->reading = reading;
    this->time = time;
}

template<typename dType, typename tType>
SensorReading<dType, tType>::SensorReading(){
    this->reading = 0,
    this->time = 0;
}
template<typename dType, typename tType>
SensorReading<dType, tType>::~SensorReading(){

}