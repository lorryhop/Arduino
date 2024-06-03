#include <DS1302.h>           // DS1302 라이브러리 헥사 선언

const int CLK = 2;            // Clock 을  5번핀 설정
const int DAT = 3;            // Data를  6번핀 설정
const int RST = 4;            // Reset을  7번핀 설정

DS1302 rtc(RST, DAT, CLK);  // DS1302  객체 설정

String str = "";
int num = 0;

void setup() 
{
  Serial.begin(9600);                 // 시리얼 통신 설정
  
  rtc.halt(false);                    // 동작 모드로 설정:false
  rtc.writeProtect(true);            // 시간 변경을 가능하게 설정:false
  
  Serial.println("DS1302RTC Test");   // 시리얼 모니터에 ("   ") 내용을 출력
  Serial.println("---------------");  // 시리얼 모니터에 ("   ") 내용을 출력

  rtc.setDate(25, 2, 2024);           // 날짜 설정(일, 월, 년도)
  rtc.setTime(00, 16, 20);             // 시간 설정(시간, 분, 초)
  rtc.setDOW(SUNDAY);                 // 요일 설정
}


void loop()
{
  Serial.print(rtc.getDateStr());   // 시리얼 모니터에 날짜 출력
  Serial.print(" > ");
  Serial.print(rtc.getTimeStr());   // 시리얼 모니터에 시간 출력
  Serial.print(" / ");
  Serial.print(rtc.getDOWStr());  // 시리얼 모니터에 요일 출력
  Serial.print(" | ");
  //Serial.println(rtc.getTimeStr().toString.substring(4,6));

  str = rtc.getTimeStr();
  Serial.print("str : ");
  Serial.print(str);

  Serial.print(" hour : ");
  Serial.print(str.substring(0,2));
  Serial.print(" min : ");
  Serial.print(str.substring(3,5));
  Serial.print(" sec : ");
  Serial.print(str.substring(6,8));

  //TEST
  if(str.substring(6,8) == "30") {
    Serial.print("OK");
  }

  Serial.println();
  delay(1000);                      // 1초의 딜레이
}
