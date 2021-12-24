#include <TM1637Display.h>
#include "WiFiEsp.h"


// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX    TX, RX를 반대로 하니까 된다.
#endif


//define microwave(초음파)
const int triggerPin = 12;
const int echoPin = 13;


//7디지트용 포트선언
const int DIO = 8; //Set the DIO pin connection to the display
const int CLK = 9; //Set the CLK pin connection to the display

TM1637Display display(CLK, DIO); //set up the 4-Digit Display.


// 와이파이
char ssid[] = "WIC";//"SH_SSID";            // your network SSID (name)
char pass[] = "with!@0919";//"lorryhop";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
int reqCount = 0;                // number of requests received

WiFiEspServer server(80);


void setup(){
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  display.setBrightness(0x0a); //set the diplay to maximum brightness
  
  
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");

  printWifiStatus();

  // start the web server on port 80
  server.begin();
}


void loop(){
  long duration = 0L;
  long distance = 0L;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  

  // 센서값 튐방지 평균함수호출
  distance = calcDistance(duration);
  
  //FND 표시창에 표시
  display.showNumberDec(distance); 
  
  
  // listen for incoming clients
  WiFiEspClient client = server.available();

  if (client) {
    Serial.println("New client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          Serial.println("Sending response");
          // send a standard http response header
          // use \r\n instead of many println statements to speedup data send
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"  
            "Refresh: 20\r\n"        // refresh the page automatically every 20 sec
            "\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html>\r\n");
          client.print("<h1>(:SWEET MONKEY:)</h1>\r\n");
          client.print("<h2>Fertilizer Water Tank Level Indicater</h2>\r\n");
          client.print("Requests received : ");
          client.print(++reqCount);
          client.print("<br>\r\n");
          client.print("Analog input distance_mm : ");
          client.print(distance);
          client.print("<br>\r\n");
          client.print("</html>\r\n");
          break;
        }

        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }

        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    // give the web browser time to receive the data
    delay(2000);

    // close the connection:
    client.stop();
    Serial.println("Client disconnected");
  }
}


void printWifiStatus(){
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}


long calcDistance(long duration) 
{
  int real_cm = 0;
  
  real_cm = (int)duration/29/2;
  
  Serial.print("real_cm = ");
  Serial.print(real_cm);
  Serial.println(" cm");
  
  return real_cm;
}
