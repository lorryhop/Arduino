/* 내아이피 1.235.41.246 */
/* 서버아이피 uws64-209 | 183.111.174.96 */

#include <ESP8266WiFi.h>  // Use this for WiFi instead of Ethernet.h
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//IPAddress server_addr(183,111,174,96);  // IP of the MySQL *server* here
IPAddress server_addr(133,186,250,80);  // IP of the MySQL *server* here

char user[] = "kevin1217";              // MySQL user login username
char password[] = "pl!@546130A";        // MySQL user login password

// WiFi card example
char ssid[] = "SH_SSID";    // your SSID
char pass[] = "lorryhop";       // your SSID Password
char INSERT_SQL[] = "INSERT INTO kevin1217.tempnhumi(temp, humi) VALUES (30, 99)";
WiFiClient client;            // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // Begin WiFi section
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while( WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // print out info about the connection:
 
    Serial.println("Connected to network");
    Serial.print("My IP address is: ");
    Serial.println(WiFi.localIP());
  
  // End WiFi section

  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    cur_mem->execute(INSERT_SQL);
    delete cur_mem;
  }
  else
    Serial.println("Connection failed.");
  conn.close();
}

void loop() {
}
