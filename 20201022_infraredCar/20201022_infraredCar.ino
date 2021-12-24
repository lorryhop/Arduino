#include <IRremote.h>


int RECV_PIN = A0; //define input pin on Arduino
IRrecv irrecv(RECV_PIN);
decode_results results;


int LED_RED = 2;

int MOTER_LEFT_CONTROL = 6;
int MOTER_LEFT_FORWARD = 7;
int MOTER_LEFT_REVERSE = 8;
int MOTER_RIGHT_CONTROL = 11;
int MOTER_RIGHT_FORWARD = 12;
int MOTER_RIGHT_REVERSE = 13;


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
  //LED핀
  pinMode(LED_RED, OUTPUT);
  
  //MOTER핀
  pinMode(MOTER_LEFT_CONTROL, OUTPUT);
  pinMode(MOTER_LEFT_FORWARD, OUTPUT);
  pinMode(MOTER_LEFT_REVERSE, OUTPUT);
  
  //MOTER핀
  pinMode(MOTER_RIGHT_CONTROL, OUTPUT);
  pinMode(MOTER_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTER_RIGHT_REVERSE, OUTPUT);

}


void loop() 
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    
    if(results.value == 0xFF6897) {
      light();//0버튼
    } else if(results.value == 0xFF30CF) {
      left();//1버튼
    } else if(results.value == 0xFF7A85) {
      right();//3버튼
    } else if(results.value == 0xFF38C7) {
      stop();//5버튼
    }
    
    delay(100);
    irrecv.resume(); // Receive the next value
  }
}


void light()
{
  Serial.println("IN LIGHT");
  
  for(int i = 0; i < 5; i++) 
  {
    digitalWrite(LED_RED, HIGH);
    delay(100);
    digitalWrite(LED_RED, LOW);
    delay(100);
  }
}


void right()
{
  Serial.println("right");
  
  digitalWrite(MOTER_LEFT_FORWARD, HIGH);
  digitalWrite(MOTER_LEFT_REVERSE, LOW);
  analogWrite(MOTER_LEFT_CONTROL, 50);
  delay(500);
}


void left()
{
  Serial.println("left");
  
  digitalWrite(MOTER_LEFT_FORWARD, LOW);
  digitalWrite(MOTER_LEFT_REVERSE, HIGH);
  analogWrite(MOTER_LEFT_CONTROL, 50);
  delay(500);
}


void stop()
{
  Serial.println("stop");
  
  digitalWrite(MOTER_LEFT_FORWARD, LOW);
  digitalWrite(MOTER_LEFT_REVERSE, LOW);

  digitalWrite(MOTER_RIGHT_FORWARD, LOW);
  digitalWrite(MOTER_RIGHT_REVERSE, LOW); 
}

  
  /*
  digitalWrite(MOTER_RIGHT_FORWARD, LOW);
  digitalWrite(MOTER_RIGHT_REVERSE, HIGH);
  analogWrite(MOTER_RIGHT_CONTROL, 150);
  delay(500) ;
 
 
  
  
  digitalWrite(MOTER_LEFT_FORWARD, LOW);
  digitalWrite(MOTER_LEFT_REVERSE, HIGH);
  analogWrite(MOTER_LEFT_CONTROL, 150); 
  delay(500) ;
  
  digitalWrite(MOTER_RIGHT_FORWARD, HIGH);   
  digitalWrite(MOTER_RIGHT_REVERSE, LOW); 
  analogWrite(MOTER_RIGHT_CONTROL, 150);
  delay(500) ; 
  
  
  
  
  digitalWrite(MOTER_LEFT_FORWARD, LOW);
  digitalWrite(MOTER_LEFT_REVERSE, LOW);
  delay(500) ;
  
  digitalWrite(MOTER_RIGHT_FORWARD, LOW);
  digitalWrite(MOTER_RIGHT_REVERSE, LOW); 
  delay(500) ;  */
