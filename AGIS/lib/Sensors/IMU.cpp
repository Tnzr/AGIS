#include <IMU.h>

MPU6050::MPU6050(String devicename, uint8_t pin){
    if (!mpu.begin())
    {
        Serial.println("Sensor init failed");
    }
    
    sensor_msg.devicename = devicename;
    sensor_msg.type = "imu";
    sensor_msg.sensor_state = sensor_state;
    sensor_msg.timestamp = getTimestamp();
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
      mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
      Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
}

JsonObject MPU6050::appendSensorItem(IMU_Sensor sensor, JsonArray &sensorArray){
    JsonObject obj = sensorArray.add<JsonObject>();
    obj["id"] = sensor.id;
    obj["axis"] = sensor.axis;
    obj["value"] = sensor.value;
    obj["unit"] = sensor.unit;
    return obj;
}

JsonObject MPU6050::VecToJson(String type, Vec3<float> imu_sensor_bundle, JsonArray &sensorArray){
    JsonObject obj = sensorArray.add<JsonObject>();
    
    JsonObject appendSensorItem;
    return obj;
}

JsonObject MPU6050::sensorStateToJson(String category, Vec3<float> vec, JsonArray &sensorArray){
    JsonObject array = sensorArray.add<JsonObject>();
    array[category][""]

    // appendSensorItem("accel", {})
    // obj[] = a.acceleration.x;
    // obj["acc_y"] = a.acceleration.y;
    // obj["acc_z"] = a.acceleration.z;



}

String MPU6050::toJSON(){
    JsonDocument doc;
    // JsonObject sensor = doc.to<JsonObject>();
    // Create a nested array named "DHT_Sensor"
    JsonObject sensor_packet = doc[sensor_name].to<JsonObject>();
    sensor_state = getSample();
    sensor_packet["device_name"] = "MPU6050";
    sensor_packet["type"] = "sensor_imu";
    sensor_packet["timestamp"] = getTimestamp();
    // holds accel, gyro, temp
    JsonObject sensor_state_json = sensor_packet["sensor_state"].add<JsonObject>();
    appendDataToJson("acc", sensor_state.acc, sensor_state_json);


    String jsonString;
    serializeJsonPretty(doc, jsonString);
    return jsonString; 
}

String getTimestamp() {
  // Get current time in seconds since epoch
  time_t now;
  time(&now);

  // Convert to UTC time
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);

  // Format time as ISO 8601 string
  char isoTime[25];
  strftime(isoTime, sizeof(isoTime), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);

  return String(isoTime);
}

IMU6 MPU6050::getSample(){
    mpu.getEvent(&a, &g, &temp);
    sensor_state.acc.x = a.acceleration.x;
    sensor_state.acc.y = a.acceleration.y;
    sensor_state.acc.z = a.acceleration.z;
    sensor_state.acc.x = g.acceleration.x;
    sensor_state.acc.y = g.acceleration.y;
    sensor_state.acc.z = g.acceleration.z;
    sensor_state.temperature = temp.temperature;
    return sensor_state;
}