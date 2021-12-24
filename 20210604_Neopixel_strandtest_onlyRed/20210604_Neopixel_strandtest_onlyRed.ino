// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    8

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 37

// Declare our NeoPixel strip object:
//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();   
  pixels.setBrightness(255);
 
  // END of Trinket-specific code.

  //strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  //strip.show();            // Turn OFF all pixels ASAP
  //strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  

}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...
  /* onlyRed 58~69
  colorWipe(strip.Color(255,   0,   0), 60000); // Red
  colorWipe(strip.Color(  0, 255,   0), 50); // Green
  colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(10);             // Flowing rainbow cycle along the whole strip
  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
*/

  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.setPixelColor(2, pixels.Color(255, 0, 0));
  pixels.setPixelColor(3, pixels.Color(255, 0, 0));
  pixels.setPixelColor(4, pixels.Color(255, 0, 0));
  pixels.setPixelColor(5, pixels.Color(255, 0, 0));
  pixels.setPixelColor(6, pixels.Color(255, 0, 0));
  pixels.setPixelColor(7, pixels.Color(255, 0, 0));
  pixels.setPixelColor(8, pixels.Color(255, 0, 0));
  pixels.setPixelColor(9, pixels.Color(255, 0, 0));
  pixels.setPixelColor(10, pixels.Color(255, 0, 0));
  pixels.setPixelColor(11, pixels.Color(255, 0, 0));
  pixels.setPixelColor(12, pixels.Color(255, 0, 0));
  pixels.setPixelColor(13, pixels.Color(255, 0, 0));
  pixels.setPixelColor(14, pixels.Color(255, 0, 0));
  pixels.setPixelColor(15, pixels.Color(255, 0, 0));
  pixels.setPixelColor(16, pixels.Color(255, 0, 0));
  pixels.setPixelColor(17, pixels.Color(255, 0, 0));
  pixels.setPixelColor(18, pixels.Color(255, 0, 0));
  pixels.setPixelColor(19, pixels.Color(255, 0, 0));
  pixels.setPixelColor(20, pixels.Color(255, 0, 0));
  pixels.setPixelColor(21, pixels.Color(255, 0, 0));
  pixels.setPixelColor(22, pixels.Color(255, 0, 0));
  pixels.setPixelColor(23, pixels.Color(255, 0, 0));
  pixels.setPixelColor(24, pixels.Color(255, 0, 0));
  pixels.setPixelColor(25, pixels.Color(255, 0, 0));
  pixels.setPixelColor(26, pixels.Color(255, 0, 0));
  pixels.setPixelColor(27, pixels.Color(255, 0, 0));
  pixels.setPixelColor(28, pixels.Color(255, 0, 0));
  pixels.setPixelColor(29, pixels.Color(255, 0, 0));
  pixels.setPixelColor(30, pixels.Color(255, 0, 0));
  pixels.setPixelColor(31, pixels.Color(255, 0, 0));
  pixels.setPixelColor(32, pixels.Color(255, 0, 0));
  pixels.setPixelColor(33, pixels.Color(255, 0, 0));
  pixels.setPixelColor(34, pixels.Color(255, 0, 0));
  pixels.setPixelColor(35, pixels.Color(255, 0, 0));
  pixels.setPixelColor(36, pixels.Color(255, 0, 0));
  pixels.show();
  
  delay(60000);
}
