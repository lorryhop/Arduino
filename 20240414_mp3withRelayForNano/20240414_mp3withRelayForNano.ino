/*
 * 영어교육용
 * 최종수정 : 20231009 시간 135초로 줄임(근데어항옆거는 업로드가 안되서 실패
 * 그래서 relayPin = 3이다
*/

#include <Wire.h>
#include <TM1637Display.h>

float sensorValue = 1000;
float filteredValue = 1000;
float sensitivity = 0.25;//높을수록 빨라진다.

//릴레이 신호핀
const int relayPin = 3;

//define microwave(초음파)
const int triggerPin = 5;
const int echoPin = 6;

//7디지트용 포트선언
const int DIO = 8;
const int CLK = 9;

TM1637Display display(CLK, DIO);

int timer;


void setup() 
{
  Serial.begin(9600);

  display.setBrightness(0x0a); //set the diplay to maximum brightness

  pinMode(relayPin, OUTPUT);   //220V 릴레이 신호핀
  
  pinMode(triggerPin, OUTPUT);   //초음파 송신핀
  pinMode(echoPin, INPUT);    //초음파 수신핀

  filteredValue = sensorValue;
}


void loop() 
{
  digitalWrite(triggerPin, LOW);   // Trig 핀 Low
  delayMicroseconds(2);   // 2us 딜레이
  digitalWrite(triggerPin, HIGH);  // Trig 핀 High
  delayMicroseconds(10);  // 10us 딜레이
  digitalWrite(triggerPin, LOW);   // Trig 핀 Low

  sensorValue = pulseIn(echoPin, HIGH);
  sensorValue = sensorValue * 170 / 1000;

  Serial.print("sensorValue: ");
  Serial.print(sensorValue); // 거리를 시리얼 모니터에 출력
  
  filteredValue = filteredValue*(1-sensitivity)+sensorValue*sensitivity;

  delay(10);
  Serial.print(" / filteredValue: ");
  Serial.print(filteredValue); // 거리를 시리얼 모니터에 출력
  Serial.print("");

  //float cm = 10650.08*pow(filteredValue,-0.935)-10;
  
  if(filteredValue >= 50 && filteredValue <= 700) {//700 = 70cm
    timer = 1100;//1100은 260초정도 되드라
  }

  if(timer > 0) {
    digitalWrite(relayPin, HIGH);   // 220V 릴레이 닫힘(ON)  
    display.showNumberDec(int(timer/10)); //Display the numCounter value;
  } else {
    digitalWrite(relayPin, LOW);   // 220V 릴레이 열림(OFF)
    display.showNumberDec(filteredValue); //Display the numCounter value;
  }
  
  if(timer > 0) {
    timer = timer-1;
    Serial.print(" / timer: ");
    Serial.print(timer);
  }

  Serial.println("");

/* 선혁이가 자꾸꺼서 주석처리 함
  if(timer > 0 && distance < 100) {//10cm 이내면 정지
    timer = 0;
    display.showNumberDec(timer); //Display the numCounter value;
    digitalWrite(relayPin, LOW);   // 220V 릴레이 열림(OFF)
    delay(2000);
  }
*/

  delay(100);
}
