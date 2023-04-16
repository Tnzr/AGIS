#pragma once
template <typename reading_t, typename time_t> struct SensorReading
{
    reading_t reading;
    time_t time;
};
