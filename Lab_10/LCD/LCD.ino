
#include <LiquidCrystal.h>
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;
//int mystr;
float b;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  lcd.print("hello, world!");
  for(int i = 0 ; i <15 ;i++){
    lcd.scrollDisplayLeft();
    delay(100);
  }
  delay(1000);
  Serial.write("Send information");
  delay(1000);
  lcd.begin(16, 1);
  Serial.begin(9600);
  startMillis = millis(); 
}

void loop() {
  ShowValFromSensors();
  delay(10);
}
 
void ShowValFromSensors(){
  lcd.setCursor(1, 5);
  b = Serial.read(); 
  currentMillis = millis();
  if (currentMillis - startMillis >= period)  
  { 
   lcd.print(b);
     startMillis = currentMillis; 
  }
}
