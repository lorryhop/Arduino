/*
  238-3-2 HC06(슬레이브코드)
 */
#include <SoftwareSerial.h>
#include <TM1637Display.h>

SoftwareSerial HC06(2, 3); // TX, RX

//초음파센서
const int TRIG = 8;
const int ECHO = 9;

//7디지트용 FND
const int DIO = 5;
const int CLK = 6;

TM1637Display display(CLK, DIO);

long duration, distance;    // 거리 측정을 위한 변수 선언

long lcdShowCount = 360; // 360은 대략 3분

void setup() {
  Serial.begin(9600); //PC-아두이노간
  HC06.begin(9600); //아두이노-블루투스모듈

  display.setBrightness(0); //set the diplay to maximum brightness

  pinMode(TRIG, OUTPUT);   //초음파 송신핀
  pinMode(ECHO, INPUT);    //초음파 수신핀

  delay(1000);
}


void loop() { // run over and over
  digitalWrite(TRIG, LOW);  // Trig 핀 Low
  delayMicroseconds(2);     // 2us 딜레이
  digitalWrite(TRIG, HIGH); // Trig 핀 High
  delayMicroseconds(10);    // 10us 딜레이
  digitalWrite(TRIG, LOW);  // Trig 핀 Low

  duration = pulseIn(ECHO, HIGH);

  distance = duration * 170 / 1000;
  Serial.println("distance : " + (String)distance + " mm");

  if(lcdShowCount >= 0) {
    display.showNumberDec(distance); //Display the numCounter value;
  } else {
    display.setBrightness(0);
    display.showNumberDec(0);
  }

  if(Serial.available()) {      // 시리얼모니터에 입력된 데이터가 있다면
    HC06.write(Serial.read());  // 블루투스를 통해 입력된 데이터 전달
  }
  
  if(distance > 0) {
    HC06.println(distance);
  }

  lcdShowCount--;
  Serial.println("lcdShowCount : " + (String)lcdShowCount + "");
  
  delay(500);
}
