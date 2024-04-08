#pragma once
#include <cstdio>

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

#include "SensorReading.tpp"