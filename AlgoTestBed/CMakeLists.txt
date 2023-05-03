cmake_minimum_required(VERSION 3.16)
project(AlgoTestBed)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)
add_executable(AlgoTestBed main.cpp ${SOURCE_FILES} lib/Algorithms.h lib/PID.h lib/FTBDLL.h lib/ReadingWindow.h )

set(SOURCE_FILES
        lib/FTBDLL.tpp
        lib/ReadingWindow.cpp
        lib/SensorReading.cpp)

target_include_directories(AlgoTestBed PUBLIC lib)
