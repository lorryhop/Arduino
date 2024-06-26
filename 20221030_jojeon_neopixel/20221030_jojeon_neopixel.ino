#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN    12

#define LED_COUNT 22

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(115200);
  delay(10); 

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  // END of Trinket-specific code.
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
}


void loop() {
  colorWipe(strip.Color(  255, 255,   255), 100); // Red
  delay(20000);
  
  colorWipe(strip.Color(  255, 0,   0), 100); // Red
  delay(10000);
  
  colorWipe(strip.Color(  0,   255, 0), 100); // Green
  delay(10000);
  
  colorWipe(strip.Color(  0,   0, 255), 100); // Blue
  delay(10000);
  
  rainbow(50);
  delay(10000);
  
  theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  //theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness
  delay(10000);
  
  theaterChaseRainbow(10); // Rainbow-enhanced theaterChase variant
  delay(10000);
  
  colorWipe(strip.Color(  0, 0,   0), 0); // off
  
  delay(1);
}


// Some functions of our own for creating animated effects -----------------

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





/*

String response = "\

  <!DOCTYPE html>\

<html>\

<head>\

<style>\

#btn{\

border: 1px solid blue;\

background-color: rgba(0,0,0,0);\

color: blue;\

padding: 5px;\

border-top-left-radius: 5px;\

border-bottom-left-radius: 5px;\

border-top-right-radius: 5px;\

border-bottom-right-radius: 5px;\

margin-right:-4px;\

height:40px;\

}\

table {\

border-collapse: collapse;\

width:500px;\

}\

table, td, th {\

border: solid 1px #cccccc;\

}\

tr {\

height:40px;\

text-align: center;\

}\

td, th {\

padding: 5px;\

}\

.set1 {\

background-color: red;\

color: white;\

text-decoration: underline;\

font-weight: bold;\

}\

#c_head {\

height:30px;\

background-color: #eeeeee;\

}\

#c_width{\

width: 500px;\

}\

</style>\

</head>\

<body>\

<h1>NOCKANDA RELAY EXAMPLE!</h1>\

<table>\

<tr id=\"c_head\">\

<th>RESULT(ON or OFF)</th>\

</tr>\

<tr>\

<td height=100 "+

style

+"><h1>"+

onoff

+"</h1></td>\

</tr>\

<tr>\

<td>\

    <button id=\"btn\" onclick=\"location.href='/ON'\">REALY ON</button>\

    <button id=\"btn\" onclick=\"location.href='/OFF'\">RELAY OFF</button>\

</td>\

</tr>\

</table>\

</body>\

</html>\

  ";

*/
