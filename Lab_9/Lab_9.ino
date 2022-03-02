#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define melodyPin 4
#define DELAY 500
int button1 = 0;
int button2 = 0;
unsigned long currentMillis;
unsigned long blink06StartMillis;
unsigned long blink1StartMillis;
unsigned long blink13StartMillis;
unsigned long blink25StartMillis;

enum {
  state0, state1, state2
} state;

int wish_melody[] = {
  NOTE_B3, 
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

int wish_tempo[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};

void setup()
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  state = state0;
  Serial.println("Enter state0");

}

void loop()
{
  button1 = digitalRead(2);
  button2 = digitalRead(3);
  
  switch(state) {
    case state0: handleState0(); break;
    case state1: handleState1(); break;
    case state2: handleState2(); break;
  }  

}

void handleState0()
{
  
  if (button1 == LOW && button2 == HIGH) {
    state = state1;
    Serial.println("Enter state1");
    delay(DELAY);
    return;
  } 
  if (button1 == HIGH && button2 == LOW) {
    state = state2;
    Serial.println("Enter state2");
    delay(DELAY);
    return;
  }
  
  digitalWrite(10,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(7,HIGH);

}

void handleState1()
{
 if (button1 == LOW && button2 == HIGH) {
   state = state0;
   Serial.println("Enter state0");
   delay(DELAY);
   return;
  }

 if (button1 == HIGH && button2 == LOW) {
   state = state2;
   Serial.println("Enter state2");
   delay(DELAY);
   return;
 }
  
 currentMillis = millis();
 blink06Hz();
 blink1Hz();
 blink13Hz();
 blink25Hz();

}

void handleState2()
{
  if(button1 == HIGH && button2 == LOW) {
    state = state0;
    Serial.println("Enter state0");
    delay(DELAY);
    return;
  } 
  
  if (button1 == LOW && button2 == HIGH) {
    state = state1;
    Serial.println("Enter state1");
    delay(DELAY);
    return;
  }
  currentMillis = millis();
  sing();
  blink06Hz();
  blink1Hz();
  blink13Hz();
  blink25Hz();
}


void sing()
{
   Serial.println(" 'We wish you a Merry Christmas'");
    int size = sizeof(wish_melody);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / wish_tempo[thisNote];
      buzz(melodyPin, wish_melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      buzz(melodyPin, 0, noteDuration);
    }
}
  
  
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; 
  long numCycles = frequency * length / 1000; 
  for (long i = 0; i < numCycles; i++) { 
    digitalWrite(targetPin, HIGH); 
    delayMicroseconds(delayValue); 
    digitalWrite(targetPin, LOW); 
    delayMicroseconds(delayValue); 
  }
  digitalWrite(13, LOW);

}
  
 
void blink06Hz() 
{
  if (currentMillis - blink06StartMillis >= 1666)  
  {
    digitalWrite(10, !digitalRead(10));  
    blink06StartMillis = currentMillis;  
  }
}

void blink1Hz() 
{
 if (currentMillis - blink1StartMillis >= 1000)  
  {
   digitalWrite(9, !digitalRead(9));  
   blink1StartMillis = currentMillis;  
 }
}
void blink13Hz() 
{
 if (currentMillis - blink13StartMillis >= 769)  
{
 digitalWrite(8, !digitalRead(8));  
  blink13StartMillis = currentMillis;  
  }
}
void blink25Hz() 
{
  if (currentMillis - blink25StartMillis >= 400)  
  {
    digitalWrite(7, !digitalRead(7));  
    blink25StartMillis = currentMillis;  
  }
}
