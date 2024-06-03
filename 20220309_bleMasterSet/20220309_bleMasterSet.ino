/*
  238-3-1 HC06(마스터코드)
 */
#include <SoftwareSerial.h>
#include <TM1637Display.h>

SoftwareSerial HC06(2, 3); // TX, RX

//피에조부저
const int BUZ = 5;

//LED
const int LED = 13;

//7디지트 FND
const int DIO = 7;
const int CLK = 8;

TM1637Display display(CLK, DIO);

long recvDistance; //수신된 초음파 거리

unsigned long time_prev, time_curr;
const long interval = 10000;

int ledState = 0;
boolean alerted = false;

int count = 200;

void setup() {
  Serial.begin(9600); //PC-아두이노간
  HC06.begin(9600); //아두이노-블루투스모듈

  display.setBrightness(0x0a);

  pinMode(BUZ, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, LOW);

  delay(1000);
}


void loop() {
  if(HC06.available()) { //블루투스에서 넘어온 데이터가 있다면
    //Serial.write(HC06.read()); //시리얼모니터에 데이터를 출력
    recvDistance = HC06.parseInt();
  }

  if(Serial.available()) {    // 시리얼모니터에 입력된 데이터가 있다면
    HC06.write(Serial.read());  // 블루투스를 통해 입력된 데이터 전달
  }

  if(recvDistance != 0) {
    Serial.println("recvDistance : " + (String)recvDistance + " mm");
    display.showNumberDec(recvDistance);
  }

  if(count == 0) {
    digitalWrite(LED, LOW);
    alerted = false;
    count = 100;
  }
  
  if(recvDistance > 30 && recvDistance < 1000) { // 1미터 내로 접근하면
    if(alerted == false) {
      tone(BUZ, 300, 150);
      tone(BUZ, 800, 200);

      for(int i = 0; i < 10; i++) {
        digitalWrite(LED, i%2);
        delay(500);
      }
      
      alerted = true;
    }
  }

  if(alerted == true) {
    count--;
  }

  Serial.println("count : " + (String)count + "");

  delay(500);
}


  /*
      unsigned long currentMillis = millis();
      
      if(currentMillis - previousMillis >= interval) { // 깜박임 주기가 지났는지 확인
        previousMillis = currentMillis; // 마지막 LED 상태 변경시간을 저장
    
        if(ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
  */
