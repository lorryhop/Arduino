
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);   //220V 릴레이 신호핀
  
  pinMode(8, OUTPUT);   //초음파 송신핀
  pinMode(9, INPUT);    //초음파 수신핀
  
  //LCD
  lcd.init();
  lcd.backlight();
}


long duration, distance;    // 거리 측정을 위한 변수 선언
int timer;

void loop() {
  digitalWrite(8, LOW);   // Trig 핀 Low
  delayMicroseconds(2);   // 2us 딜레이
  digitalWrite(8, HIGH);  // Trig 핀 High
  delayMicroseconds(10);  // 10us 딜레이
  digitalWrite(8, LOW);   // Trig 핀 Low

  duration = pulseIn(9, HIGH);

  distance = duration * 170 / 1000;

  Serial.print("distance: ");
  Serial.print(distance); // 거리를 시리얼 모니터에 출력
  Serial.println(" mm");
  
  Serial.println("");
  
  Serial.print("timer: ");
  Serial.print(timer); // 타이를 시리얼 모니터에 출력
  Serial.println(" sec");
  
  if(distance < 700) {
    timer = 3;
  }
  
  if(timer > 0) { 
    digitalWrite(13, LOW);   // 220V 릴레이 닫힘(ON)  
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("220V RELAY");
    lcd.setCursor(0,1); lcd.print("LIGHT ON ("); lcd.print(timer, 1); lcd.print(")");
  } else {
    digitalWrite(13, HIGH);   // 220V 릴레이 열림(OFF)
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("220V RELAY");
    lcd.setCursor(0,1); lcd.print("LIGHT OFF");
  }
  
  if(timer > 0) {
    timer = timer-1;
  }
  

  delay(1000);
}
