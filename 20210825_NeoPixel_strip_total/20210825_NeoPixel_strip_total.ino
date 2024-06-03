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


//사용한 예제
//https://blog.daum.net/rockjjy99/2610
//


#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

const char* ssid = "WIC";
const char* password = "with!@0919";


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    12

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
 
WiFiServer server(80);
 
// setup() function -- runs once at startup --------------------------------
 
void setup() {
  Serial.begin(115200);
  delay(10); 
 
    // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
 
  // END of Trinket-specific code.
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
}
 
 
// loop() function -- runs repeatedly as long as board is on ---------------
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
 
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
 
 
  // Match the request
  String value = "";
 
  if (request.indexOf("/LED=RED") != -1) {
    colorWipe(strip.Color(  255, 0,   0), 50); // Red
    value = "red";
  }
 
  if (request.indexOf("/LED=GREEN") != -1){
    colorWipe(strip.Color(  0,   255, 0), 50); // Green
    value = "green";
  }
 
  if (request.indexOf("/LED=BLUE") != -1){
    colorWipe(strip.Color(  0,   0, 255), 50); // Blue
    value = "blue";
  }
 
  if (request.indexOf("/LED=RAINBOW") != -1){
    rainbow(10);
    value = "rainbow";
  }
 
  if (request.indexOf("/LED=THEATERCHASE") != -1){
    // Do a theater marquee effect in various colors...
    theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
    theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
    theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness
  
    theaterChaseRainbow(10); // Rainbow-enhanced theaterChase variant
    value = "theaterChase";
  }
 
  if (request.indexOf("/LED=OFF") != -1) {
    colorWipe(strip.Color(  0, 0,   0), 0); // off
    value = "off";
  }
 
  
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("NeoPixel is now: ");
  if(value == "red") {
    client.print("red");  
  } else if(value == "green") {
    client.print("green");
  } else if(value == "blue") {
    client.print("blue");
  } else if(value == "rainbow") {
    client.print("rainbow");
  } else if(value == "theaterChase") {
    client.print("theaterChase");
  } else if(value == "off") {
    client.print("off");
  }
  
  client.println("<br><br>");
  client.println("<font size=11>Click <a href=\"/LED=RED\">here</a> Turn RED</font><br>");
  client.println("<font size=11>Click <a href=\"/LED=GREEN\">here</a> Turn GREEN</font><br>");
  client.println("<font size=11>Click <a href=\"/LED=BLUE\">here</a> Turn BLUE</font><br>");
  client.println("<font size=11>Click <a href=\"/LED=RAINBOW\">here</a> Turn RAINBOW</font><br>");
  client.println("<font size=11>Click <a href=\"/LED=THEATERCHASE\">here</a> Turn THEATERCHASE</font><br>");
  client.println("<font size=11>Click <a href=\"/LED=OFF\">here</a> Turn OFF</font><br>");
  client.println("</html>");
 
  delay(1);
 
  Serial.println("Client disconnected");
  Serial.println("");
 
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
