
int tmp36 = A0;
int photoRes = A1;
int sensoreVal = 0;
float tempReading;
String read;

void setup() {
  pinMode(tmp36, INPUT);
  pinMode(photoRes, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  Serial.write( measureTemp());
  delay(10);
  Serial.write(measureLight());
  delay(10);
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
