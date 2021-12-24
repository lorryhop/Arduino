#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 5 // 위모스 보드는 3번핀에 꽂는다

#define NUMPIXELS 8 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//기타 정의
#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels


void setup() 
{
  Serial.begin(115200);
  
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}


void loop() 
{
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
