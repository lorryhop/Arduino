/**
 * 열대밀림&공룡소리(적외선)
*/
#include <Wire.h>
#include <TM1637Display.h>


//릴레이 신호핀
const int relayPin = 4;

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
  
  if(distance < 3000) {
    timer = 200;//35;
  }
  
  if(timer > 0) {
    Serial.println("11111111");
    //digitalWrite(relayPin, HIGH);   // 220V 릴레이 닫힘(ON)     1번버전하고 이부분만 틀림.1번버전이 잘못된것임 ㅠㅠ
    digitalWrite(relayPin, LOW);   // 220V 릴레이 닫힘(ON)  
    display.showNumberDec(timer); //Display the numCounter value;
  } else {
    Serial.println("222222222");
    //digitalWrite(relayPin, LOW);   // 220V 릴레이 열림(OFF)
    digitalWrite(relayPin, HIGH);   // 220V 릴레이 열림(OFF)
    display.showNumberDec(distance); //Display the numCounter value;
  }
  
  if(timer > 0) {
    timer = timer-1;
  }
  
  delay(1000);
}
