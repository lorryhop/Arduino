//사용한 예제
//https://blog.daum.net/rockjjy99/2610
//

#include <ESP8266WiFi.h>

const char* ssid = "SH_SSID";
const char* password = "lorryhop";

int ledPin = 4;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10); 

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

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
}


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

  int value = LOW;
  
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }

  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");

  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }

  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> Turn relay ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> Turn relay OFF<br>");
  client.println("</html>");

  delay(1);

  Serial.println("Client disconnected");
  Serial.println("");
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
