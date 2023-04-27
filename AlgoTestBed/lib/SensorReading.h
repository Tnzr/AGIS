#pragma once
#include <cstdio>
#include "Algorithms.h"
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
        friend std::ostream& operator<< (std::ostream& os, const SensorReading& sensorReading) {

            os << "[" << sensorReading.reading << "," << sensorReading.time << "]";
            return os;
        }
};

template<typename dType, typename tType>
void SensorReading<dType, tType>::update_reading(dType reading, tType t) {
    this->reading = reading;
    this->time = t;
}

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