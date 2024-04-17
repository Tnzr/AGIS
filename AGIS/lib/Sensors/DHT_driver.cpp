#include <DHT_driver.h>
#include <iostream>

#define DHTTYPE DHT11

DHT_driver::DHT_driver(uint8_t data): dht(data, DHTTYPE), data_pin(data) {
    dht.begin();
    id = printf("DHT_Sensor_Pin%d", data_pin);
    stats = sampleRead();
    pinMode(data_pin, INPUT);
}


JsonObject DHT_driver::appendDatatoJson(SensorData data, JsonArray &sensorArray){
    JsonObject obj = sensorArray.add<JsonObject>();
    obj["title"] = data.title;
    obj["id"] = data.id;
    obj["value"] = data.value;
    obj["unit"] = data.unit;
    return obj;
}


String DHT_driver::toJSON(){
    JsonDocument doc;
    // JsonObject sensor = doc.to<JsonObject>();
    // Create a nested array named "DHT_Sensor"
    JsonArray sensorArray = doc["DHT_Sensor"].to<JsonArray>();
    sampleRead();
    SensorData tempData = {"Temperature", "temperature", stats.temperature, "&deg;C"};
    SensorData humData = {"Humidity", "humidity", stats.humidity, "&percnt;"};
    JsonObject tempObj = appendDatatoJson(tempData, sensorArray); 
    JsonObject humObj = appendDatatoJson(humData, sensorArray); 
    String jsonString;
    serializeJsonPretty(doc, jsonString);
    return jsonString; 
}

void DHT_driver::setSensorName(String name){ //DHT_Sensor_ID
    id = printf("DHT_Sensor_%s", name);
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

