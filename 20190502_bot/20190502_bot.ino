#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16,2);

const int redLed = 7;
const int greenLed = 8;
const int triggerPin = 12;
const int echoPin = 13;
const int speakerPin = 4;
const int pirPin = 2;
const int servoPin = 3;

const int wr1 = 5;
const int wr2 = 6;
const int wl1 = 9; 
const int wl2 = 10;

long duration = 0;

int pirVal = 0;

  int trigVal = 0;
  int findAngle[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  int findDistance[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  int minIdx = 0;
  
Servo Motor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(redLed, OUTPUT);      //LED 적색
  pinMode(greenLed, OUTPUT);    //LED 녹색
  
  pinMode(triggerPin, OUTPUT);  //초음파센서 발신부
  pinMode(echoPin, INPUT);      //초음파센서 수신부

  pinMode(speakerPin, OUTPUT);

  pinMode(pirPin, INPUT);

  pinMode(wr1, OUTPUT);
  pinMode(wr2, OUTPUT);
  pinMode(wl1, OUTPUT);
  pinMode(wl2, OUTPUT);
  
  lcd.init();
  lcd.backlight();

  Motor.attach(servoPin);  //  9 번 핀에 모터
  Serial.begin(9600);
  
}


void loop() {
  // put your main code here, to run repeatedly:
/*  digitalWrite(wr1, LOW);
  digitalWrite(wr2, HIGH);
  delay(300);
  digitalWrite(wr1, LOW);
  
  digitalWrite(wl1, HIGH);
  digitalWrite(wl2, LOW);
  delay(300);
  digitalWrite(wl1, LOW);
*/
  
  pirVal = digitalRead(pirPin);
  Serial.print("pirVal : ");
  Serial.println(pirVal);

  Motor.write(0); // 초기 각도 0 으로 : 옵션
  
  for(int angle = 0; angle <= 12; angle = angle+1) {
    Motor.write(angle*10);
    Serial.print("R angle : ");Serial.println(angle*10);
    delay(100);
  }

  for(int angle = 12; angle >= 0 ; angle = angle-1) {
    Motor.write(angle*10);
    Serial.print("L angle : ");Serial.print(angle*10);

    trigVal = trigger();
    Serial.print(" / trigVal : ");Serial.println(trigVal);
    if(trigVal >= 3) {
      findAngle[angle] = angle;
      findDistance[angle] = trigVal;
    }
    delay(100);
  }

  //배열에 담긴 각도 로그
  for(int i = 0; i < 12; i++) {
    Serial.print("findAngle val : ");Serial.println(findAngle[i]);
    Serial.print("findDistance val : ");Serial.println(findDistance[i]);
  }

  //제일 가까운 거리의 각도 찾기
  for(int i = 0; i < 12; i++) {
    if(i > 0 && findDistance[i] < findDistance[minIdx]) {
      minIdx = i;
      Serial.print("#############");
      Serial.print(minIdx);
      Serial.print("#############");
    }
  }
  delay(100);

  Serial.print("minIdx : ");Serial.println(minIdx);
  Serial.print("minIdx val : ");Serial.println(findDistance[minIdx]);

  if(findDistance[minIdx] <= 100) {
    Motor.write(minIdx*10);
    
    lcd.setCursor(0, 0);  
    lcd.print("DISTANCE : ");
    lcd.print(findDistance[minIdx]);
    lcd.setCursor(0, 1);
    
    if(findDistance[minIdx] < 10) {
      lcd.print("OUR LOVE, Kevin!!");
      tone(speakerPin, 1500, 300);//핀번호, 음의높낮이(주파수), 음의지속시간
    } else if(findDistance[minIdx] < 20) {
      lcd.print("Daddy loves you!!");
      tone(speakerPin, 1500, 300);//핀번호, 음의높낮이(주파수), 음의지속시간
    } else if(findDistance[minIdx] < 30) {
      lcd.print("Mommy loves you!!");  
      tone(speakerPin, 1500, 300);//핀번호, 음의높낮이(주파수), 음의지속시간
    } else if(findDistance[minIdx] < 40) {
      lcd.print("Let's go camping!!");  
    } else if(findDistance[minIdx] < 50) {
      lcd.print("Play sports!!");  
    } else if(findDistance[minIdx] < 60) {
      lcd.print("Nice too meet you!!");  
    } else if(findDistance[minIdx] < 70) {
      lcd.print("Dad create me!!");  
    } else if(findDistance[minIdx] < 80) {
      lcd.print("Welcome, KEVIN!");  
    } else {
      lcd.print("Are you.. Kevin?");  
    }
    
    tone(speakerPin, 500, 300);//핀번호, 음의높낮이(주파수), 음의지속시간
    delay(100);
    
    //바퀴 움직이기
    if(minIdx > 6) {
      digitalWrite(wr1, LOW);
      digitalWrite(wr2, HIGH);
      delay(100);
      delay(minIdx*50);
      digitalWrite(wr2, LOW);
      Serial.print("RRRRRRRRRRRRRRRRRRRRRRRR");
    } else {
      digitalWrite(wl1, HIGH);
      digitalWrite(wl2, LOW);
      delay(200);
      delay(minIdx*50*3);
      digitalWrite(wl1, LOW);
      Serial.print("LLLLLLLLLLLLLLLLLLLLLLLL");
    }

    digitalWrite(redLed, HIGH);
    delay(500);
    digitalWrite(redLed, LOW);
    delay(500);
  } else {
    digitalWrite(greenLed, HIGH);
    delay(500);
    digitalWrite(greenLed, LOW);
    delay(500);
  }

  lcd.clear();
  //Motor.write(0); // 초기 각도 0 으로 : 옵션
  delay(3000);
  
}


long trigger() {
  long distance_mm = 0;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance_mm = Distance(duration);

  return distance_mm/10;
}

  
long Distance(long time) {
  long distanceCalc;
  distanceCalc = ((time/2.9)/2);
  
  return distanceCalc;
}
