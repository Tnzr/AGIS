#include <DHT_driver.h>

#define DHTTYPE DHT11

DHT_driver::DHT_driver(uint8_t data): dht(data, DHTTYPE), data_pin(data) {
    dht.begin();
    id = String("DHT_Sensor_Pin") + data_pin;
}


JsonObject DHT_driver::appendDatatoJson(SensorData data, JsonArray &sensorArray){
    JsonObject obj = sensorArray.add<JsonObject>();
    obj["title"] = data.title;
    obj["id"] = data.id;
    obj["value"] = data.value;
    obj["unit"] = data.unit;
    return obj;
}


void DHT_driver::appendReadings(JsonDocument &doc, const DHT_Measurement &reading){
    JsonArray sensorArray = doc["DHT_Sensor"].to<JsonArray>();
    SensorData tempData = {"Temperature", "temperature", reading.temperature, "&deg;C"};
    SensorData humData = {"Humidity", "humidity", reading.humidity, "&percnt;"};
    appendDatatoJson(tempData, sensorArray);
    appendDatatoJson(humData, sensorArray);
}

String DHT_driver::toJSON(){
    JsonDocument doc;
    appendReadings(doc, sampleRead());
    String jsonString;
    serializeJsonPretty(doc, jsonString);
    return jsonString; 
}

void DHT_driver::setSensorName(String name){ //DHT_Sensor_ID
    id = "DHT_Sensor_" + name;
}

float DHT_driver::getHumidity(){
    float hum = dht.readHumidity();
    return hum;
}

float DHT_driver::getTemperature(){
    return dht.readTemperature();
}

DHT_Measurement DHT_driver::sampleRead(){
    stats.temperature = getTemperature();
    stats.humidity = getHumidity();
    return stats;
}
