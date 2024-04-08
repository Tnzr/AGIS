#pragma once
#include "SensorReading.h"
#include "FTBDLL.h"
#include <vector>
#include <list>

// Window Tail Resampling for Asynchonous Discrete-Time Integration
const short unsigned int FORWARD = 1;
const short unsigned int BACKWARDS = 0;

template<typename dType, typename tType> class ReadingWindow : public FTBDLL<dType>{
    private:

        FTBDLL<SensorReading<dType, tType>> readingsList;
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
        dType getArea(Node<dType>* start, short unsigned int direction);
        dType areaBetweenReadings(Node<SensorReading<dType, tType>>* start, Node<SensorReading<dType, tType>>* end);


};

#include "ReadingWindow.tpp"

