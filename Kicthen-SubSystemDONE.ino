// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN A0     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11     //DHT 11 sensor model


DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor.
int ventilatorPin = 9; //for heat, used with temp sensor
int dehumidiferPin = 6;
int IRDistanceSensor = 5;
int time = 0;

float findTempVolt(float x){
  return ((5*x)/22) - 6.34;
}

float findHumidityVolt(float x){
  return (x/10) - 5;
}

float findAnalogueVolt(float x){
    return (x/5) * 1023;
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test."));
  pinMode(ventilatorPin, OUTPUT);
  pinMode(dehumidiferPin, OUTPUT);
  pinMode(IRDistanceSensor,INPUT);
  dht.begin();
  
}

void loop() {
  
  delay(2000); // Readings taken every 2 seconds.
  time = time + 2;
  Serial.println(time);

  

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();
  //Serial.println(findTempVolt(30.5));
  

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor."));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  
  Serial.print(F("%  Temperature: "));
  Serial.print(temp);
  Serial.print(F("°C \n"));
  

  
  if(temp >= 50) {
    Serial.print("EMERGENCY: PLEASE VACATE THE BUILDING AND CALL FOR ASSISTANCE");
  }
  else if(temp >= 28) {
    //Power on ventilator with intensity propotional to diff. between temp - 28
    Serial.print(F("Temperature LED voltage: "));
    Serial.print(findTempVolt(temp)+1.5);
    Serial.print(F("V \n"));
    analogWrite(ventilatorPin,findAnalogueVolt(findTempVolt(temp) + 1.5));
    if (time >= 10){ //>= 600 in reality, 10 for testing
      Serial.print("Please check the kitchen for appliances that may have been left on by accident. \n");
     //time = time - 120;
    }
  }
  else{
    digitalWrite(ventilatorPin,LOW);
  }

  if(humidity >= 65) {
    //Serial.println(findAnalogueVolt(humidity));
    Serial.print(F("Humidity LED voltage: "));
    Serial.print(findHumidityVolt(humidity));
    Serial.print(F("V \n"));
    analogWrite(dehumidiferPin,findAnalogueVolt(findHumidityVolt(humidity)));
    }else{
    digitalWrite(dehumidiferPin,LOW);
  }

  if(digitalRead(IRDistanceSensor)==LOW)  {
     //Motion Detected
     time = 0;
     Serial.println("MOTION DETECTED");
  }
}
