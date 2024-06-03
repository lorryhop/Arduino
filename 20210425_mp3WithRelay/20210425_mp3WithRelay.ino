/*
 * 영어교육용
 * 최종수정 : 20231009 시간 135초로 줄임(근데어항옆거는 업로드가 안되서 실패
 * 그래서 relayPin = 4이다
*/

#include <Wire.h>
#include <TM1637Display.h>


//릴레이 신호핀
const int relayPin = 7;

//define microwave(초음파)
const int triggerPin = 13;
const int echoPin = 12;

//7디지트용 포트선언
const int DIO = 8;
const int CLK = 9;

TM1637Display display(CLK, DIO);

long duration, distance;    // 거리 측정을 위한 변수 선언
int timer;


void setup() 
{
  Serial.begin(9600);

  display.setBrightness(0x0a); //set the diplay to maximum brightness

  pinMode(relayPin, OUTPUT);   //220V 릴레이 신호핀
  
  pinMode(triggerPin, OUTPUT);   //초음파 송신핀
  pinMode(echoPin, INPUT);    //초음파 수신핀
}


void loop() 
{
  digitalWrite(triggerPin, LOW);   // Trig 핀 Low
  delayMicroseconds(2);   // 2us 딜레이
  digitalWrite(triggerPin, HIGH);  // Trig 핀 High
  delayMicroseconds(10);  // 10us 딜레이
  digitalWrite(triggerPin, LOW);   // Trig 핀 Low

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 170 / 1000;

  Serial.print("distance: ");
  Serial.print(distance); // 거리를 시리얼 모니터에 출력
  Serial.println(" mm");
  
  Serial.print("timer: ");
  Serial.print(timer); // 타이를 시리얼 모니터에 출력
  Serial.println(" sec");

  Serial.println("");
  
  if(distance >= 50 && distance <= 700) {//70cm
    timer = 135;
  }
  
  if(timer > 0) {
    digitalWrite(relayPin, HIGH);   // 220V 릴레이 닫힘(ON)  
    display.showNumberDec(timer); //Display the numCounter value;
  } else {
    digitalWrite(relayPin, LOW);   // 220V 릴레이 열림(OFF)
    display.showNumberDec(distance); //Display the numCounter value;
  }
  
  if(timer > 0) {
    timer = timer-1;
  }

/* 선혁이가 자꾸꺼서 주석처리 함
  if(timer > 0 && distance < 100) {//10cm 이내면 정지
    timer = 0;
    display.showNumberDec(timer); //Display the numCounter value;
    digitalWrite(relayPin, LOW);   // 220V 릴레이 열림(OFF)
    delay(2000);
  }
*/

  delay(1000);
}
