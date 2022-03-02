#include <Servo.h>
#define echoPin 5
#define triggerPin 6
#define DELAY 500


Servo myServo;
int putpin = 0;
int val;
int button1 = 0;
int button2 = 0;
int itterator = 1;
long duritation;
int distanse;

enum {
  state0, state1, state2
} state;

void setup() {
  state = state0;
  myServo.attach(10);
  Serial.begin(9600);
  pinMode(4, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.println("Enter state0");
}

void loop() {
  button1 = digitalRead(4);
  button2 = digitalRead(3);
  
  switch(state) {
    case state0: state0handler(); break;
    case state1: state1handler(); break;
    case state2: state2handler(); break;
  }  
}

void state0handler() {
  
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
  
  val = analogRead(putpin);
  val = map(val,0, 1023, 0, 180);
  myServo.write(val);
  delay(15);
}

void state1handler() {
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
  // sonic radar
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);
  duritation = pulseIn(echoPin, HIGH);
  distanse = duritation*0.034/2;
  Serial.println(distanse);
  
  
}

void state2handler() {
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
  
  if(val <= 0) {
    itterator = 1;
  }
  if(val >= 1023) {
    itterator = -1;
  }

  //delay(1);
  Serial.println(val);
  Serial.println(distanse);
  val += itterator;   
  myServo.write(map(val,0, 1023, 0, 180));
}
