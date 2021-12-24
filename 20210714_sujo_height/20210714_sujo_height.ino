/**
 * 수조 물높이(적외선)
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_STRIP_PIN 9 // On Trinket or Gemma, suggest changing this to 2

#define NUMPIXELS 8 // Popular NeoPixel ring size

Adafruit_NeoPixel strip(NUMPIXELS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);


//define microwave(초음파)
const int triggerPin = 3;
const int echoPin = 4;


long duration = 0;

void setup() 
{
  Serial.begin(9600);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  //rainbow(3000);            // Flowing rainbow cycle along the whole strip
}


void loop() 
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  long hgt = Distance(duration);

  Serial.print("distance = ");
  Serial.print(hgt);
  Serial.println(" cm");

  if(hgt <= 10) {
    colorWipe(strip.Color(255,   255,   255),  8, 10);
  } else if(hgt <= 11 && hgt <= 15) {
    colorWipe(strip.Color(255,   255,   255),  7, 10);
  } else if(hgt >= 16 && hgt <= 20) {
    colorWipe(strip.Color(255,   255,   255),  6, 10);
  } else if(hgt >= 21 && hgt <= 25) {
    colorWipe(strip.Color(255,   255,   255),  5, 10);
  } else if(hgt >= 26 && hgt <= 30) {
    colorWipe(strip.Color(255,   255,   255),  4, 10);
  } else if(hgt >= 31 && hgt <= 35) {
    colorWipe(strip.Color(255,   255,   255),  3, 10);
  } else if(hgt >= 36 && hgt <= 40) {
    colorWipe(strip.Color(255,   255,   255),  2, 10);
  } else if(hgt >= 45 && hgt <= 50) {
    colorWipe(strip.Color(255,   255,   255),  1, 10);
  } else if(hgt <= 51 && hgt <= 100) {
    colorWipe(strip.Color(255,   255,   255),  8, 10);
  } else if(hgt <= 101 && hgt <= 150) {
    colorWipe(strip.Color(255,   255,   255),  7, 100);
  } else if(hgt >= 151 && hgt <= 200) {
    colorWipe(strip.Color(255,   255,   255),  6, 100);
  } else if(hgt >= 201 && hgt <= 250) {
    colorWipe(strip.Color(255,   255,   255),  5, 100);
  } else if(hgt >= 251 && hgt <= 300) {
    colorWipe(strip.Color(255,   255,   255),  4, 100);
  } else if(hgt >= 301 && hgt <= 350) {
    colorWipe(strip.Color(255,   255,   255),  3, 100);
  } else if(hgt >= 351 && hgt <= 400) {
    colorWipe(strip.Color(255,   255,   255),  2, 100);
  } else if(hgt >= 450) {
    colorWipe(strip.Color(255,   255,   255),  1, 100);
  }
  
  strip.clear();

  delay(200);
}


void colorWipe(uint32_t color, int height, int wait) 
{
  for(int i=0; i<height; i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}


void rainbow(int wait) 
{
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<NUMPIXELS; i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}


long Distance(long time)
{
  long distanceCalc;
  //distanceCalc = ((time/2.9)/2)/10;
  distanceCalc = time/58;
  
  return distanceCalc;
}
