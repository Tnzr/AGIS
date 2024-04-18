#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>
// #include <Adafruit_BusIO_Register.h>
#include <Adafruit_Sensor.h>
#include <time.h>


// struct Vec3 {
    // float x, y, z;
// };

template<typename T> struct Vec3 {
    T x, y, z;
};

typedef struct IMU6 {
    Vec3<float> acc;
    Vec3<float> gyro;
    float temperature;
    // Vec3<float> mag;
} IMU6;


typedef struct IMU_Packet {
    String devicename;
    String type;
    String timestamp;
    IMU6 sensor_state;
    
} IMU_Packet;

typedef struct IMU_Sensor {
    String id;
    String axis;
    float value;
    String unit;
} IMU_Sensor;

String getTimestamp();

class MPU6050 {
    private:
        // uint8_t SCL;
        // uint8_t SDA;
        sensor_t sensor;
        sensors_event_t a, g, temp;
        String sensor_name;
        Adafruit_MPU6050 mpu;
        IMU6 sensor_state;
        IMU_Packet sensor_msg;
        JsonObject appendDataToJson(IMU6 data, JsonArray &sensorArray);
    public:
        MPU6050(String devicename, uint8_t pin);
        Vec3<float> getAcceleration();
        Vec3<float> getGyro();
        IMU6 getSample();
        String toJSON();
        String toJSON(Vec3<float> vector);
        JsonObject appendSensorData(IMU_Sensor sensor, JsonArray &sensorArray);
        JsonObject sensorStateToJson(String sensor_name, Vec3<float> vec, JsonArray &sensorArray);
        JsonArray VecToJsonArray(String type, Vec3<float> vector, JsonArray &jArray, String unit);
        JsonObject appendSensorItem(IMU_Sensor sensor, JsonArray &sensorArray);
        

};

