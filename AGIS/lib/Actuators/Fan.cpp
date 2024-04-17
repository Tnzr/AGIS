#include <Fan.h>



JsonObject Fan::appendDatatoJson(SensorData data, JsonArray &sensorArray){
    JsonObject obj = sensorArray.add<JsonObject>();
    obj["title"] = data.title;
    obj["id"] = data.id;
    obj["value"] = data.value;
    obj["unit"] = data.unit;
    return obj;
}

String Fan::toJSON(){
    JsonDocument doc;
    // JsonObject sensor = doc.to<JsonObject>();
    // Create a nested array named "DHT_Sensor"
    JsonArray sensorArray = doc["Fan"].to<JsonArray>();
    SensorData rpm = {"RPM", "rpm", status.currentRPM, "RPM"};
    SensorData cfm = {"CFM", "cfm", status.cfm, "ft^3/min"};
    appendDatatoJson(rpm, sensorArray); 
    appendDatatoJson(cfm, sensorArray); 
    String jsonString;
    serializeJsonPretty(doc, jsonString);
    return jsonString; 
}

Fan::Fan(uint8_t driving_pin, uint8_t sensor_pin, 
unsigned short int max_rpm, unsigned short int cfm, unsigned long updateDelta){
        this->driving_pin = driving_pin;
        this->currentRPM = 0;
        this->deltaTime = 0; 
        this->lastUpdate = millis(); 
        this->maxRPM = max_rpm; // max rev / min
        this->cfm = cfm; // cubic feet / minute
        this->updateDelta = (updateDelta) ? // min_delta (ms), 0 for auto
                            this->updateDelta = updateDelta :
                            this->updateDelta = 60,000/this->maxRPM;
        pinMode(this->driving_pin, OUTPUT);
        
        if(sensor_pin){
            this->sensor_pin = sensor_pin;
            pinMode(this->sensor_pin, INPUT);
            attachInterrupt(digitalPinToInterrupt(sensor_pin), 
                (void (*)())this->rev_tick(), RISING);
        }
}

void *Fan::rev_tick(){
    this->now = millis();
    this->tickCount++;
    this->deltaTime = this->now-this->lastUpdate;

  // TODO 
  // deltaTime/tick timeout
    if (this->deltaTime >= this->updateDelta){
        this->updateTickFrequency();
        this->lastUpdate = this->now;
    }
    return nullptr;
}

void Fan::updateTickFrequency(){
    // pulse * 6E4 (ms/Min) / (deltaTime (ms) * pulse/REV )
    this->currentRPM = this->tickCount * 6E4 / (this->deltaTime * this->tpr);
    this->tickCount = 0;
}

unsigned short int Fan::getRPM(){
    return currentRPM;
}

void Fan::setPWM(float dcycle){
    analogWrite(this->driving_pin, int(dcycle*255));
}