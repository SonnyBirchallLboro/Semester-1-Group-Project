 
#include <math.h>
const int Light_thresholdvalue=10;   //The threshold for which the LED should turn on.
float Light_Rsensor; //Resistance of sensor in K
const int LEDPin = 12;


//LDR Constants
const int LDR_ldrPin = A3;
const int LDR_threshold = 500;


//Motion Sensor
const int Motion_SIGNAL_PIN = 2;



//Temp Constants
const int Temp_B = 4275;               // B value of the thermistor
const int Temp_R0 = 100000;            // R0 = 100k
const int pinTempSensor = A1;     // Grove - Temperature Sensor connect to A1 need to change
const int TempLEDPin = 13;


//Temp Setup
#if defined(ARDUINO_ARCH_AVR)
#define debug  Serial
#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define debug  SerialUSB
#else
#define debug  Serial
#endif
//Temp Setup end





void setup() {​​​​​​
  Serial.begin(9600);                //Start the Serial connection
  pinMode(TempLEDPin,OUTPUT);            //Set the LED on Digital 12 as an OUTPUT
  pinMode(LEDPin, OUTPUT);
  pinMode (LDR_ldrPin, INPUT);
  pinMode(Motion_SIGNAL_PIN, INPUT);   //Set motion sensor input
}​​​​​​




void loop() {​​​​​​
  //Light sensor getter
  int Light_sensorValue = analogRead(0);
  Light_Rsensor=(float)(1023-Light_sensorValue)*10/Light_sensorValue;


 //LDR Getter
  int LDR_ldrStatus = analogRead(LDR_ldrPin);


 //Motion Setup
 int motion; //value for high or low to set 2nd pin


 //Temp Setup
 int a = analogRead(pinTempSensor);
 float Temp_R = 1023.0/a-1.0;
 Temp_R = Temp_R0*Temp_R;
 float temperature = 1.0/(log(Temp_R/Temp_R0)/Temp_B+1/298.15)-273.15; // convert to temperature via datasheet
 


//Detect Motion??
  if(digitalRead(Motion_SIGNAL_PIN) == HIGH)
  {​​​​​​
    Serial.println("movement detected");
    motion = 1;
  }​​​​​​ 
  else 
  {​​​​​​
    Serial.println("no movement detected");
    motion = 0;
  }​​​​​​


  
  // sensor select statement
  if((Light_Rsensor>Light_thresholdvalue)&&(LDR_ldrStatus <= LDR_threshold)&&(motion == 1))
  {​​​​​​
    digitalWrite(LEDPin,HIGH);
  }​​​​​​
  else
  {​​​​​​
  digitalWrite(LEDPin,LOW);
  }​​​​​​


 //Temp Sensor select
 if (temperature > 30) 
 {​​​​​​
 digitalWrite(TempLEDPin, HIGH);
 }​​​​​​
 else
 {​​​​​​
 digitalWrite(TempLEDPin, LOW);
 }​​​​​​
}​​​​​​















