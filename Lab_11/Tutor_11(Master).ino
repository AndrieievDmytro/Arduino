#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;
float b;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte ROWS = 1; 
const byte COLS = 3; 

char keys[ROWS][COLS] = {{'1','2','3'}};
byte rowPins[ROWS] = { 10 };
byte colPins[COLS] = { 9,8,7} ;

Keypad kpd = Keypad( makeKeymap(keys), rowPins,
  colPins, ROWS, COLS );

void setup() {
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(8,INPUT);
  Wire.begin(); // Master
  Serial.begin(9600);
  startMillis = millis(); 
  lcd.begin(16, 1);
  
  lcd.print("There is/are ");
  lcd.print(countDevices());
  lcd.print(" device(s) connected");
  for(int i = 0 ; i <34 ;i++){
    lcd.scrollDisplayLeft();
    delay(50);
  }
  
}

void loop() {
	
  char key = kpd.getKey();
  if(key == '1')
  {
  	lcd.print("1");
  	delay(100);	
    lcd.clear();  
  }else if (key == '2')
  {
   readData(2);
  }else if (key == '3')
  {
   readData(3);  
  } 
}
 
int countDevices(){
  int nDevices = 0;
  byte error , address;
  for (address = 1; address < 127; address++) 
  {
     Wire.beginTransmission(address);
     error = Wire.endTransmission();
    
      if (error == 0)
      {
          if (address< 7)
          { 
              nDevices++;
          }
     }else if(error == 4)
     {
       return -1;
     }
   }
  if( nDevices == 0 )
  {
    return 0;
  }
  return nDevices;
}  

void readData(int a){
 Wire.requestFrom(a,2);
  while(1 < Wire.available())
  {
    int a = Wire.read();
    int b = Wire.read();
    currentMillis = millis();
    if (currentMillis - startMillis >= 500)  
    { 
      lcd.print("Light level ");
    lcd.print(a);
      delay(500);
      lcd.clear();
      lcd.print("Temperature ");
      lcd.print(b);
      delay(500);
      lcd.clear();
    startMillis = currentMillis;
    }
  }
}
