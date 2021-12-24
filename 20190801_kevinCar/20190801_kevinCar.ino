#define RELEASE  0
#define FORWARD  1
#define BACKWARD 2
#define LEFT     3
#define RIGHT    4

byte enablePin = 5;
byte motorPin1 = 8;
byte motorPin2 = 9;
byte motorPin3 = 10;
byte motorPin4 = 11;

int joyStickPin = 7;


int getX()
{
  int val = 0;
  val = analogRead(A1);
  return val;
}

int getY()
{
  int val = 0;
  val = analogRead(A0);
  return val;
}

int getZ()
{
  int val = 0;
  val = digitalRead(joyStickPin);
  return val;
}


void motorMove(int key)
{
  switch(key)
  {
    case 0:
            digitalWrite(motorPin1,HIGH);
            digitalWrite(motorPin2,HIGH);
            digitalWrite(motorPin3,HIGH);
            digitalWrite(motorPin4,HIGH);
            break;
    case 1:
            digitalWrite(motorPin1,HIGH);
            digitalWrite(motorPin2,LOW);
            digitalWrite(motorPin3,HIGH);
            digitalWrite(motorPin4,LOW);
            break;
    case 2:
            digitalWrite(motorPin1,LOW);
            digitalWrite(motorPin2,HIGH);
            digitalWrite(motorPin3,LOW);
            digitalWrite(motorPin4,HIGH);
            break;
    case 3:
            digitalWrite(motorPin1,HIGH);
            digitalWrite(motorPin2,LOW);
            digitalWrite(motorPin3,LOW);
            digitalWrite(motorPin4,LOW);
            break;
    case 4:
            digitalWrite(motorPin1,LOW);
            digitalWrite(motorPin2,LOW);
            digitalWrite(motorPin3,HIGH);
            digitalWrite(motorPin4,LOW);
            break;
  }
}  


void setup() 
{
  Serial.begin(9600);

  pinMode(enablePin,OUTPUT); 
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(motorPin3,OUTPUT);
  pinMode(motorPin4,OUTPUT);  

  //for joystick set
  pinMode(joyStickPin, INPUT_PULLUP);

  motorMove(FORWARD);
  Serial.print("moter forward!!");
  delay(500);
  motorMove(RELEASE);
}


void loop() 
{
  int x = getX();
  int y = getY();
  int z = getZ();
  
  
  Serial.print(x);      // X축 값이 표기됩니다.
  Serial.print("  ");   
  Serial.print(y);      // Y축 값이 표기 됩니다.
  Serial.print("  ");   
  Serial.println(z);    // Z축(스위치) 값이 표기됩니다.
  delay(100);  


  //int speed = map(analogRead(A0), 0, 1023, 0, 255); //가변저항기의 입력값
  //analogWrite(enablePin, speed);

  if(x > 400 && x < 600 && y > 400 && y < 600) {
    motorMove(RELEASE);  
  } else if (x < 100 && y > 400 && y < 600) {
    motorMove(FORWARD);
  } else if (x > 900 && y > 400 && y < 600) {
    motorMove(BACKWARD);
  } else if (x > 400 && x < 600 && y > 900) {
    motorMove(LEFT);
  } else if (x > 400 && x < 600 && y < 100) {
    motorMove(RIGHT);
  } else {
    motorMove(RELEASE);
  }
  delay(500); 
} 
