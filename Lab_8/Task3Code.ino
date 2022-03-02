//Turns from 0-180 180-0 only when button is pressed 

const int motorDirPin = 5; 
const int motorPWMPin = 6; 
const int EnablePin = 9;	
const int LED = 13;
const int encoderPinA = 2;
const int encoderPinB = 3;
int encoderPos = 0;
int button1 = 0;
const float ratio = 360./180.611/24.;
float Kp = 15;
float targetDeg = 0;

void doEncoderA()
{  
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;
}
void doEncoderB()
{  
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;
}

void doMotor(bool dir, int vel)
{
  digitalWrite(motorDirPin, dir);
  digitalWrite(LED, dir);
  analogWrite(motorPWMPin, dir?(255 - vel):vel);
}

void setup()
{
  Serial.begin(9600);
  
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
  
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
  
  pinMode(LED, OUTPUT);
  pinMode(motorDirPin, OUTPUT);
  pinMode(EnablePin, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  
  digitalWrite(EnablePin, 1);
}

void loop()
{
  int b = button1;
  button1 = digitalRead(7);
  float targetDegI = analogRead(0);
  float motorDeg = float(encoderPos)*ratio;
  float error = targetDeg - motorDeg;
  float control = Kp*error;
  

  if (button1 == LOW){
	state2handler(error, b);
  }else{
    state0handler(targetDegI);
  }

  doMotor((control>=0)?HIGH:LOW, min(abs(control), 254));
  Serial.print("targetDeg : ");
  Serial.print(targetDeg);
  Serial.print("encoderPos : ");
  Serial.print(encoderPos);
  Serial.print("   motorDeg : ");
  Serial.print(float(encoderPos)*ratio);
  Serial.print("   error : ");
  Serial.print(error);
  Serial.print("    control : ");
  Serial.print(control);
  Serial.print("    motorVel : ");
  Serial.println(min(abs(control), 254)); 
}

void state0handler(float targetDegI) {
  targetDeg = map(targetDegI,0, 1023, 0, 270);  
}

  
void state2handler(float error, int b) {
  if ( b == LOW && button1 == HIGH){
  	targetDeg = 180;
    encoderPos = 0;
  }
  if ( abs(error) < 2 ){
  	targetDeg = abs( 180 - targetDeg );
  }
}