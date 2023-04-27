#include <Arduino.h>
#include <Actuators.h>
#include <Sensors.h>
#include <Controllers.h>
#include <Algorithms.h>


// #include <FTBDLL.cpp>
#define WATERPUMP_PIN 15
#define IWFSENSOR_PIN 2
#define LED 2
#define print(x)  Serial.print(x)
// PLEASE CHECK THE LIB DIRECTORY FOR PROGRESS
// The main binary will be developed once all necessary classes are defined


SensorReading<double, double> sensorReading = SensorReading<double, double>(5,4);
  FTBDLL<SensorReading<double, double>> dll = FTBDLL<SensorReading<double, double>>(4);
  // FTBDLL<double> dll = FTBDLL<double>(2);
  WaterFlowSensor wfsensor = WaterFlowSensor(IWFSENSOR_PIN, 2.5, 10);
  WaterPump waterPump = WaterPump(WATERPUMP_PIN, 300);


void setup() {
  // put your setup code here, to run once:

  
  // FTBDLL<Node<int>> dll(10);
  Serial.begin(9600);
  // while (!Serial);
  pinMode(LED, OUTPUT);
  Serial.println("Setup Complete.");
  
// FTBDLL<SensorReading<double, double>> dll = FTBDLL<SensorReading<double, double>>(2);
}

void loop() {
	// put your main code here, to run repeatedly:
	// dll = FTBDLL<SensorReading<double, double>>(4);
	Serial.println(dll.getSize());
	digitalWrite(LED, HIGH);
	Serial.println("LED is on");
	delay(1000);
	digitalWrite(LED, LOW);
	Serial.println("LED is off");
	delay(1000);
	// Serial.println("Loop: "+80);
	dll.display();
	delay(5000); 

	while (true){
		dll.display();

		if(!dll.isFull()){
			digitalWrite(LED, HIGH);  
			delay(500);
			Serial.println(sensorReading);
			print(dll.push_back(sensorReading));
			digitalWrite(LED, LOW);  
			delay(500);
		}
		else{
			print("List is Full\n");
			while (true);
			digitalWrite(LED, HIGH);  

		}
		// dll.display();
	}


}

