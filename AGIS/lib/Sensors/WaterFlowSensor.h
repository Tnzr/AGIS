// WaterPump.h

#ifndef WaterFlowSensor_h
#define WaterFlowSensor_h

class WaterFlowSensor{
  
  private:
    int sensor_pin;
    float tick_to_volume;
    volatile long pulse_count;
    void increase();
    
  public:
    WaterFlowSensor(int sense_pin, float conversion);
  }


#endif WaterFlowSensor_h
