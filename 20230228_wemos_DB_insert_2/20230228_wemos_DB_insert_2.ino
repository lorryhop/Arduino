// WIFI 설정
#include <ESP8266WiFi.h>        // ESP8266 WIFI
char ssid[] = "SH_SSID";     // 사용하고자 하는 WIFI 이름
char password[] = "lorryhop";   // WIFI 비밀번호
 
// MariaDB 설정
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
WiFiClient client;            // 이더넷 대신 WIFI 사용
MySQL_Connection conn((Client *)&client);
 
char INSERT_SQL[] = "INSERT INTO kevin1217.tempnhumi(pw, name) VALUES (%s, %s)";    // 쿼리 입력
char query[128];
byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
 
IPAddress server_addr(133,186,250,80);  // DB주소
char db_user[] = "kevin1217";              // MariaDB ID
char db_password[] = "pl!@546130A";        // MariaDB PW
 
 
void setup() {
  Serial.begin(115200);
 
  // 와이파이를 연결한다.
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  // MariaDB를 연결한다.
  Serial.println("Mysql Connecting...");
  if (conn.connect(server_addr, 3306, db_user, db_password)) {
    delay(1000);
  } else{
    Serial.println("Mysql Connection failed.");
    conn.close();
  }
}

 
void loop() {
  sprintf(query, INSERT_SQL, "2", "3");
  Serial.println("Recording data.");
  Serial.println(query);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute(query);
  delete cur_mem;
  delay(2000);
}
