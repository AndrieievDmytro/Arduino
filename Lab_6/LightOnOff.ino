/* Task 1 "Blink" */
void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(1000); 
  digitalWrite(13, LOW);
  delay(1000); 
}

/* Task 2 "Blink with fade" */
int brightness = 0;

void setup()
{
  pinMode(9, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(1000); 
  
  for (brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(9, brightness);
    delay(1000); 
  }
}

/* Task 3 Switch (sequential on / off) */

int pbuttonPin = 5;
int relayPin =13;

int val = 0;
int lightON =0;
int pushed = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode (pbuttonPin,INPUT);
}

void loop()
{
  val = digitalRead(pbuttonPin);
   if (val == HIGH && lightON == LOW){
  pushed = 1-pushed;
  delay(100);
   }
   
   lightON = val;
   
   if (pushed == HIGH){
		Serial.println("Light on");
		digitalWrite (relayPin, LOW);
   }else {
		Serial.println("Light OFF");
		digitalWrite(relayPin, HIGH);
   }
   delay(100);
}



/* Task 4 */

int pbuttonPin = 5;
int relayPin =13;

int val = 0;
int lightON =0;
int pushed = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode (pbuttonPin,INPUT_PULLUP);
}

void loop()
{
  val = digitalRead(pbuttonPin);
   if (val == HIGH && lightON == LOW){
  pushed = 1-pushed;
  delay(100);
   }
   
   lightON = val;
   
   if (pushed == HIGH){
		Serial.println("Light on");
		digitalWrite (relayPin, LOW);
   }else {
		Serial.println("Light OFF");
		digitalWrite(relayPin, HIGH);
   }
   delay(100);
}
/* Task 5 */
int pbuttonPin = 5;
int relayPin =13;

int val = 0;
int lightON =0;
int pushed = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode (pbuttonPin,INPUT_PULLUP);
}

void loop()
{
  val = digitalRead(pbuttonPin);
   if (debounceButton(val) == HIGH && lightON == LOW){
  pushed = 1-pushed;
  delay(100);
   }
   
   lightON = val;
   
   if (pushed == HIGH){
		Serial.println("Light on");
		digitalWrite (relayPin, LOW);
   }else {
		Serial.println("Light OFF");
		digitalWrite(relayPin, HIGH);
   }
   delay(100);
}

boolean debounceButton(boolean state)
{
	boolean stateNow = digitalRead(pbuttonPin);
	if(state!=stateNow){
		delay(10);
		stateNow = digitalRead(pbuttonPin);
	}		
	return stateNow;
}

Task 6 "Serial print (Hello world) "

void setup()
{
Serial.begin(115200);
}

void loop()
{
  Serial.println("Hello world");
  }
} 

/*
void setup()
{
Serial.begin(115200);
}

void loop()
{
  int val =  digitalRead(5);
  if(!val){
  Serial.println("Hello world");
  }
} 
*/
