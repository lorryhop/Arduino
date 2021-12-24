// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <RtcDS1302.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define SCK_PIN 2   //보드의 CLK 핀 입력
#define IO_PIN 3    //보드의 DAT 핀 입력
#define RESET_PIN 4 //RST 핀 입력

//릴레이 신호핀
#define RELAY_1 8
#define RELAY_2 9

//기타 정의
#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

// DS1302 클래스 생성(시간)
RtcDS1302 rtc(RESET_PIN, IO_PIN, SCK_PIN);


void setup() 
{
  Serial.begin(115200);
  
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  // END of Trinket-specific code.
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  //RTC 설정
  rtc.halt(false);                //DS1302 동작 시작
  //myDS1302.halt(true);          //DS1302 대기 모드로 동작
  
  rtc.writeProtect(false);        //데이터 쓰기 동작
  //myDS1302.writeProtect(true);  //데이터 쓰기 금지

  //초기 1회 셋팅
  rtc.setDOW(THURSDAY);           //요일 기록 : MONDAY ~ SUNDAY
  rtc.setDate(6, 22, 2021);       //날짜 기록 : dd/mm/yyyy
  rtc.setTime(14, 05, 00);        //시간 기록 : hh/mm/ss (※ 24시간 단위)

  //220V 릴레이 신호핀
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
}


void loop() 
{
  Serial.print("DATE ==> ");
  Serial.println(myDS1302.getDateStr(2,1,'-')); //날짜 불러오기 dd-mm-yyyy 형식
  Serial.print("TIME ==> ");
  Serial.println(myDS1302.getTimeStr()); //시간 불러오기 hh:mm:ss 형식
  Serial.print("DAY ==> ");
  Serial.println(myDS1302.getDOWStr()); //요일 불러오기
  delay(1000);
  
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(100, 100, 100));
  }
  pixels.show();

  delay(10);
  
  type1();
  type2();
  type3();
  
  delay(5000);
  
  //delay(1000*60);//1분
  //delay(1000*60*60);//1시간
  //delay(1000*60*60*24);//하루

 if(1==2) {
    digitalWrite(RELAY_1, HIGH);
    delay(500);
    digitalWrite(RELAY_1, LOW);
    delay(500);
    digitalWrite(RELAY_2, HIGH);
    delay(500);
    digitalWrite(RELAY_2, LOW);
    delay(500);
  }
}


void type1()//모두빨간색
{
  for(int j=0; j<NUMPIXELS; j++) {
    pixels.setPixelColor(j, pixels.Color(255, 0, 0));
  }
  pixels.show();
}


void type2()//모든색 순차로 보여주기
{
  for(int i=0; i<3; i++) {
    for(int j=0; j<NUMPIXELS; j++) {
      if(i==0) pixels.setPixelColor(j, pixels.Color(255, 0, 0));
      if(i==1) pixels.setPixelColor(j, pixels.Color(0, 255, 0));
      if(i==2) pixels.setPixelColor(j, pixels.Color(0, 0, 255));
      pixels.show();

      delay(100);
    }
  }
}


void type3()//각색 전체 디밍
{
  for(int i=0; i<10; i++) {
    for(int j=0; j<NUMPIXELS; j++) {
      pixels.setPixelColor(j, pixels.Color(i*25, 0, 0));
      Serial.print("[UP]type3 i val : ");Serial.print(i);Serial.print(" / ");Serial.print("type3 j val : ");Serial.println(j);
      
      delay(5);
    }
    pixels.show();
  }

  for(int i=0; i<10; i++) {
    for(int j=0; j<NUMPIXELS; j++) {
      pixels.setPixelColor(j, pixels.Color(255-(i*25), 0, 0));
      Serial.print("[DOWN]type3 i val : ");Serial.print(i);Serial.print(" / ");Serial.print("type3 j val : ");Serial.println(j);
      
      delay(5);
    }
    pixels.show();
  }
}
