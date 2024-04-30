#include <IMU.h>

MPU6050::MPU6050(String devicename, uint8_t pin){
    if (!mpu.begin())
    {
        Serial.println("Sensor init failed");
    }
    sensor_state;
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

JsonObject MPU6050::appendSensorItemToArray(IMU_Sensor sensor, JsonArray &sensorArray){
    JsonObject sensorObj = sensorArray.add<JsonObject>();
    sensorObj["id"] = sensor.id;
    sensorObj["axis"] = sensor.axis;
    sensorObj["value"] = sensor.value;
    sensorObj["unit"] = sensor.unit;
    return sensorObj;
}

JsonObject MPU6050::getJsonFromMetric(IMU_Sensor metric, JsonObject sensorObj){
    sensorObj["id"] = metric.id;
    sensorObj["axis"] = metric.axis;
    sensorObj["value"] = metric.value;
    sensorObj["unit"] = metric.unit;
    return sensorObj;
}

// type: acc
JsonArray MPU6050::VecToJsonArray(String type, Vec3<float> vec, JsonArray &sensorArray, String unit=""){
    String axis[] = {"X", "Y", "Z"};
    String idx = String("IMU_")+String(type)+String("_")+String(axis[0]);
    IMU_Sensor sensor_unit_x = {idx, String(axis[0]), vec.x, unit};
    appendSensorItemToArray(sensor_unit_x, sensorArray);  
    String idy = String("IMU_")+String(type)+String("_")+String(axis[1]);
    IMU_Sensor sensor_unit_y = {idy, String(axis[1]), vec.y, unit};
    appendSensorItemToArray(sensor_unit_y, sensorArray);  
    String idz = String("IMU_")+String(type)+String("_")+String(axis[2]);
    IMU_Sensor sensor_unit_z = {idz, String(axis[2]), vec.z, unit};
    appendSensorItemToArray(sensor_unit_z, sensorArray);  
    // for (String ax: axis) {
    //   String id = String("IMU_")+String(type)+String("_")+String(axis[0]);
    //   IMU_Sensor sensor_unit_x = {id, String(axis[0]), vec.x, unit};
    //   appendSensorItemToArray(sensor_unit_x, sensorArray);  
    // }

    return sensorArray;
}

JsonObject MPU6050::sensorStateToJson(String category, IMU6 sensor_state, JsonObject &obj){
    // JsonObject obj = sensorArray.add<JsonObject>();
    JsonArray acc_array = obj["acc"].add<JsonArray>();
    JsonArray gyro_array = obj["gyro"].add<JsonArray>();
    VecToJsonArray("acc", sensor_state.acc, acc_array, "m/s^2");
    VecToJsonArray("acc", sensor_state.gyro, gyro_array, "rad/s");
    IMU_Sensor temp = {"IMU_temp", "temp", sensor_state.temperature, "C"};
    JsonObject temp_json = obj["temp"].add<JsonObject>();
    getJsonFromMetric(temp, temp_json);
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
    // appendDataToJson("acc", sensor_state.acc, sensor_state_json);
    sensorStateToJson("", sensor_state, sensor_state_json);
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