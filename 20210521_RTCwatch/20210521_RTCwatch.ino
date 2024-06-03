#include <DS1302.h>
#include <TM1637Display.h>

#define SCK_PIN 2     //보드의 CLK 핀 입력
#define IO_PIN 3      //보드의 DAT 핀 입력
#define RESET_PIN 4   //RST 핀 입력

//7디지트용 포트선언
//#define DIO_PIN 6
//#define CLK_PIN 7


//DS1302 클래스 생성
DS1302 rtc(RESET_PIN, IO_PIN, SCK_PIN);

//7디지트용 클래스
//TM1637Display display(CLK_PIN, DIO_PIN);


//millis를 쓰기위한 변수선언
unsigned long elapse_time;

Time t;

void setup() 
{
  Serial.begin(9600);

  //display.setBrightness(0x0a); //set the diplay to maximum brightness  

  //RTC 설정
  rtc.halt(false);            //DS1302 동작 시작
  //rtc.halt(true);           //DS1302 대기 모드로 동작
  
  rtc.writeProtect(false);  //데이터 쓰기 동작
  //rtc.writeProtect(true);     //데이터 쓰기 금지

  //초기 1회 셋팅
  rtc.setDOW(MONDAY);       //요일 기록 : MONDAY ~ SUNDAY
  rtc.setDate(6,28,2021);     //날짜 기록 : dd/mm/yyyy
  rtc.setTime(15,30,00);      //시간 기록 : hh/mm/ss (※ 24시간 단위)

}


void loop() 
{
  Serial.print("DAY ==> ");
  Serial.println(rtc.getDOWStr());  //요일 불러오기
  Serial.print("DATE ==> ");
  Serial.println(rtc.getDateStr()); //날짜 불러오기 dd-mm-yyyy 형식
  Serial.print("TIME ==> ");
  Serial.println(rtc.getTimeStr()); //시간 불러오기 hh:mm:ss 형식
  Serial.println();



  // Get data from the DS1302
  t = rtc.getTime();
  
  // Send date over serial connection
  Serial.print("Year : ");
  Serial.println(t.year, DEC);
  Serial.print("Month : ");
  Serial.println(rtc.getMonthStr());
  Serial.print("day : ");
  Serial.println(t.date, DEC);
  
  // Send Day-of-Week and time
  Serial.print("DOW(monday 1th) : ");
  Serial.println(t.dow, DEC);
  Serial.print("Hour : ");
  Serial.println(t.hour, DEC);
  Serial.print("Min : ");
  Serial.println(t.min, DEC);
  Serial.print("Sec : ");
  Serial.println(t.sec, DEC);

  

  //millis함수(49.7日이 지나면 (오버플로우가 발생하여) 0ms 로 초기화 됩니다.)
  elapse_time = millis();
  Serial.print("elapse time: ");
  Serial.println(elapse_time); // 프로그램 시작후 지난 시간 출력



  //display.showNumberDec(t.hour); //Display the numCounter value;
  
  
  delay(1000);
}
