#pragma once
#include <SensorReading.h>
#include <vector>
#include <list>
#include "FTBDLL.h"
// Window Tail Resampling for Asynchonous Discrete-Time Integration

template<typename dType, typename tType> class ReadingWindow : public FTBDLL
{
private:
    /* data */
    std::list<SensorReading<dType, tType>> readings;
    // TODO
    // MAKE CUSTOM LIST CONTAINER
    dType X;
    dType dX;
    dType intX;
    tType tWindow;
    tType tCutoff;
    size_t maxNodes;
    dType samplePoint(tType position, SensorReading<dType, tType> recent, SensorReading<dType, tType> older);
    void offsetReadings(tType offset);
    void resampleTail(tType cutoff, SensorReading<dType, tType> first, SensorReading<dType, tType> last);
    int resampleByDelta(tType delta, SensorReading<dType, tType> first, SensorReading<dType, tType> last);
    void resetNode();
    void deltaDownsample(tType delta);
    bool tailOverflow();

public:
    ReadingWindow(tType tWindow = 1000, size_t max_readings = 10);
    ~ReadingWindow();
    void addReading(dType value, tType time);


};