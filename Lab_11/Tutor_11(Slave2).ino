#include <Wire.h>
int tmp36 = A0;
int photoRes = A1;
int sensoreVal = 0;
float tempReading;


void setup() {
  Wire.begin(3);
  pinMode(tmp36, INPUT);
  pinMode(photoRes, INPUT);
  Serial.begin(9600);
  Wire.onRequest(requestEvent);
}

void loop() {
  
}

int measureTemp(){
  tempReading = analogRead(tmp36);
  float voltage = tempReading * 5.0 /1023.0 ;
  float tempC = (voltage - 0.5) *100;
  return (int)tempC;
}

int measureLight(){
sensoreVal = analogRead(photoRes);
int light = map(sensoreVal, 0, 1023, 0, 255);
 return light;
 delay(100);
}

void requestEvent(){
	Wire.write(measureLight());
  	delay(10);
  	Wire.write(measureTemp());
	delay(10);
}
