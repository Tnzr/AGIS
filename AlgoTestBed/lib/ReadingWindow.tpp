#include "ReadingWindow.h"


template<typename dType, typename tType> 
ReadingWindow<dType, tType>::ReadingWindow(tType tWindow, size_t max_readings){
    this->readings.reserve(max_readings);
    this->tWindow = tWindow;
}

template<typename dType, typename tType>
void ReadingWindow<dType, tType>::offsetReadings(tType offset){
    for(unsigned int i = 0; i < this->readings.size(); i++){
        this->readings[i] += offset;
    }
}

template<typename dType, typename tType> 
void ReadingWindow<dType, tType>::resampleTail(tType cutoff, SensorReading<dType, tType> recent, SensorReading<dType, tType> older){
    if (recent.time > cutoff && cutoff > older.time){
        // Change the time and value of the closest node to that of the sampled cutoff point
        older.time = cutoff;
        // older.reading = map(cutoff, older.time, recent.time, older.reading, recent.reading); MAPS TO INTS ONLY
        
        // Add the difference between node and the sampled cutoff
        older.reading = this->samplePoint(cutoff, recent, older);
    }
}

template<typename dType, typename tType> 
int ReadingWindow<dType, tType>::resampleByDelta(tType delta, SensorReading<dType, tType> first, SensorReading<dType, tType> last){
    if (last.time-first.time < delta)
    {
        
    }else{
        return 0;
    }
}

template<typename dType, typename tType> 
void ReadingWindow<dType, tType>::deltaDownsample(tType delta){ // Delta is Half the Periodic Rate
    // If Next node is less than delta time away, erase the node
    for(unsigned int i = 0; i < this->readings.size()-2; i++){
        while (i+1 < this->readings.size() && this->readings[i+1].time-this->readings[i].time <  delta ){
           this->readings[i];
        }
    }

    
}


template<typename dType, typename tType> 
dType ReadingWindow<dType, tType>::samplePoint(tType position, SensorReading<dType, tType> recent, SensorReading<dType, tType> older){
        return older.reading + (recent.reading-older.reading)(position-older.time)/(recent.time-older.time);
}

template<typename dType, typename tType> 
bool ReadingWindow<dType, tType>::tailOverflow(){
    if (this->readings.size() >= 2)
    {
        return this->readings[0].reading < this->tCutoff;
    } else {
        return false;
    }
}


template<typename dType, typename tType> 
void ReadingWindow<dType, tType>::addReading(dType value, tType time){
    SensorReading<dType, tType> reading = {value, time}; // Init reading struct
    this->readings.insertPresent(reading); // Add reading to back of list
    if(this->tailOverflow()){ // if the oldest node is past the time window
        
    }


}

template<typename dType, typename tType> 
dType ReadingWindow<dType, tType>::areaBetweenReadings(Node<SensorReading<dType, tType>>* start, Node<SensorReading<dType, tType>>* end){
    
}

template<typename dType, typename tType> 
dType ReadingWindow<dType, tType>::getArea(Node<dType>* start, short unsigned int direction){
    direction = ( direction == 0 || direction == 1) ? direction : 0;
    dType integral = 0;
    for (Node<dType>* i = start; 
        i != ( direction ? this->head_node : this->present ); 
        i = direction ? i->next : i->prev){

            if (direction)
            {
                integral = this->areaBetweenReadings(i, i->next);

            }else{
                integral = this->areaBetweenReadings(i, i->prev);
            }
            
            
    }
    return integral * (direction ? 1 : -1);
}