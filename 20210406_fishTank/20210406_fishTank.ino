// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Servo - Version: Latest 
#include <Stepper.h>

#define LED_PIN_1 6     //keyes 8 strip
#define LED_PIN_2 7     //keyes 8 strip
#define LED_STRIP_PIN 8 //noepixel

#define NUMPIXELS 8       // keyes strip size
#define NUMSTRIPPIXELS 22 // NeoPixel strip size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels_1(NUMPIXELS, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_2(NUMPIXELS, LED_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip(NUMSTRIPPIXELS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

const int stepsPerRevolution = 64;
Stepper myStepper(stepsPerRevolution,5,3,4,2); 

void setup() {
  Serial.begin(9600);
  
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  
  //pixels_1.begin(); //keyes 8 strip(uesd)
  //pixels_2.begin(); //keyes 8 strip(uesd)
  
  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(150); // Set BRIGHTNESS to about 1/5 (max = 255)

  myStepper.setSpeed(300);
}

void loop() 
{
  Serial.println("loop start");
  
  sequence();
  
  pixel_1_white();
  pixel_2_white();
  
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(255,   0,   0), 10); // Red
  colorWipe(strip.Color(  0, 255,   0), 10); // Green
  colorWipe(strip.Color(  0,   0, 255), 10); // Blue

  // Do a theater marquee effect in various colors...
  //theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  //theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  //theaterChase(strip.Color(  0, 127,   0), 50); // Green, half brightness
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(30);             // Flowing rainbow cycle along the whole strip
  theaterChaseRainbow(1000); // Rainbow-enhanced theaterChase variant

  colorWipeStop(strip.Color(255, 255, 255), 50); // White

/*
  pixels_1.clear();
  pixels_1.setPixelColor(0, pixels_1.Color(255, 255, 255));
  pixels_1.setPixelColor(1, pixels_1.Color(255, 255, 255));
  pixels_1.setPixelColor(2, pixels_1.Color(255, 255, 255));
  pixels_1.setPixelColor(3, pixels_1.Color(255, 255, 255));
  pixels_1.setPixelColor(4, pixels_1.Color(255, 255, 255));
  pixels_1.setPixelColor(5, pixels_1.Color(255, 255, 255));
  pixels_1.setPixelColor(6, pixels_1.Color(255, 255, 255));
  pixels_1.setPixelColor(7, pixels_1.Color(255, 255, 255));
  pixels_1.show();

  pixels_2.clear();
  pixels_2.setPixelColor(0, pixels_2.Color(255, 255, 255));
  pixels_2.setPixelColor(1, pixels_2.Color(255, 255, 255));
  pixels_2.setPixelColor(2, pixels_2.Color(255, 255, 255));
  pixels_2.setPixelColor(3, pixels_2.Color(255, 255, 255));
  pixels_2.setPixelColor(4, pixels_2.Color(255, 255, 255));
  pixels_2.setPixelColor(5, pixels_2.Color(255, 255, 255));
  pixels_2.setPixelColor(6, pixels_2.Color(255, 255, 255));
  pixels_2.setPixelColor(7, pixels_2.Color(255, 255, 255));
  pixels_2.show();
  
  pixels_1.clear();
  pixels_2.clear();
  strip.clear();
*/
  
  //delay(120000);
  delay(10000);
  
  steping();
}




////////////////////////////////
// function list
////////////////////////////////

void pixel_1_white()
{
  for(int i=0; i<NUMPIXELS; i++) {
    pixels_1.setPixelColor(i, pixels_1.Color(255, 255, 255));
  }
  pixels_1.show();
}


void pixel_2_white()
{
  for(int i=0; i<NUMPIXELS; i++) {
    pixels_2.setPixelColor(i, pixels_2.Color(255, 255, 255));
  }
  pixels_2.show();
}


void sequence()//모든색 순차로 보여주기
{
  for(int i=0; i<3; i++) {
    for(int j=0; j<NUMPIXELS; j++) {
      if(i==0) pixels_1.setPixelColor(j, pixels_1.Color(31*(j+1), 0, 0));
      if(i==1) pixels_1.setPixelColor(j, pixels_1.Color(0, 31*(j+1), 0));
      if(i==2) pixels_1.setPixelColor(j, pixels_1.Color(0, 0, 31*(j+1)));
      pixels_1.show();

      delay(DELAYVAL);
    }
  }

  for(int i=0; i<3; i++) {
    for(int j=0; j<NUMPIXELS; j++) {
      if(i==0) pixels_2.setPixelColor(j, pixels_2.Color(31*(j+1), 0, 0));
      if(i==1) pixels_2.setPixelColor(j, pixels_2.Color(0, 31*(j+1), 0));
      if(i==2) pixels_2.setPixelColor(j, pixels_2.Color(0, 0, 31*(j+1)));
      pixels_2.show();

      delay(DELAYVAL);
    }
  }
}


void steping()
{
  // 시계 방향으로 한바퀴 회전
  for(int i=0; i<64; i++) {// 64*96=6144:한바퀴   64*32=2048:1/3바퀴
    myStepper.step(-stepsPerRevolution);
  }

  delay(500);
}


// Some functions of our own for creating animated effects -----------------
void colorWipeStop(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  }
  strip.show();                          //  Update strip to match
  delay(wait);                           //  Pause for a moment
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents 
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
