
int val = 0;
int pushed = 0;
int pdelay = 0;
int test = 8;

enum {
  red = 2, redYellow = 3, green = 4, yellow = 5
}state;


void setup()
{
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green, OUTPUT);
  state = red;
     
  pinMode (6,INPUT_PULLUP);
  
  
}

void loop()
{
    
 
  
  val = digitalRead(6);

  if(val == LOW){
    
  delay(1000); 
    switch(state){
      case(red): 

          digitalWrite (red, HIGH);
          digitalWrite (yellow, LOW);
          digitalWrite (green, LOW);
       
         state = redYellow; 
       
      break;
      case(redYellow):
      
          digitalWrite (red, HIGH);
          digitalWrite (yellow, HIGH);
          digitalWrite (green, LOW);
                state = green; 
       
      break;
      case (green):
      
          digitalWrite (red, LOW);
          digitalWrite (yellow, LOW);
          digitalWrite (green, HIGH);
       
         state = yellow; 
       
      
      break;
      case (yellow):
      
          digitalWrite (red, LOW);
          digitalWrite (yellow, HIGH);
          digitalWrite (green, LOW);
           
         state = red; 
      
      break;
    
    }
  }
  
 }


