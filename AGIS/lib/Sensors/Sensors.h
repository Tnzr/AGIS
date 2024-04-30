#pragma once
#include <WaterFlowSensor.h>
#include <Joystick.h>

typedef struct SensorData {
    String title;
    String id;
    float value;
    String unit;
} SensorData;


// typedef struct IMU_Packet {
//     String dimension;
//     String sensor_id;
// };

// typedef struct Vec3_Message {
//     Vec3<float> acc;
//     Vec3<float> gyro;
//     Vec3<float> mag;
// }