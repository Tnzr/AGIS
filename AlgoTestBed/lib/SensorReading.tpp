#include "SensorReading.h"


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

template<typename dType, typename tType>
void SensorReading<dType, tType>::update_reading(dType reading, tType t) {
    this->reading = reading;
    this->time = t;
}