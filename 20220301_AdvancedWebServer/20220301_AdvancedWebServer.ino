#include <ESP8266WiFi.h>
#include "mainPage.html"
#include <ArduinoOTA.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "SH_SSID";
const char *password = "lorryhop";

#define load0  0                    // Realy 컨트롤 핀

bool L1Status = HIGH;               // HIGH=Realy OFF, LOW=Realy ON
AsyncWebServer server(80);          // server on port 80
AsyncWebSocket webSocket("/ws");    // websocket

int minuteToOff = 0;                  // 타이머 잔여시간을 저장할 변수
unsigned long prevTimer = 0;          // 타이머 설정시간을 저장할 변수

void setup() {                      
  pinMode(load0, OUTPUT);             // Realy 컨트롤용 핀 지정
  digitalWrite(load0, L1Status);      // 기동시 Realy Off 상태로 설정

  Serial.begin(115200);               // 디버깅용 시리얼 포트

  setupCONNECTION();                  // 와이파이 네트워크 접속
  setupOTA();                         // OTA 기동
  setupWEBSOCKET();                   // Websocket 활성화
  setupMAINPAGE();                    // 웹서버 기동
}

void loop() {                           
  ArduinoOTA.handle();
  webSocket.cleanupClients();

  unsigned long currentMillis = millis();

  // 타이머 설정 후 1분 경과때마다 타이머를 1분식 감소시키고 
  // 0분이 되면 릴레이 OFF & 현상태를 접속한 클라이언트에 통보
  if (minuteToOff > 0 && currentMillis - prevTimer > 60000) { 
    prevTimer = currentMillis;
    minuteToOff--;                                    
    if (minuteToOff == 0) {                           
      L1Status = HIGH;
      digitalWrite(load0, L1Status);                  
    }
    noticeForClient(); 
  }
}


void setupCONNECTION() {
  WiFi.begin(ssid, password);          // WIFI네트워크에 접속 시작!
  Serial.println("\n");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }  
  Serial.println('\n');
  Serial.println("Connected!");
  Serial.print("IP address:\t");     
  Serial.println(WiFi.localIP());     // 할당받은 IP주소 표시
}

void setupMAINPAGE() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", MAIN_page);
  });
  server.begin();
}

void setupOTA() {
    // Port defaults to 8266
  ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("OTA Ready");
}

void setupWEBSOCKET() {
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  server.addHandler(&webSocket);
  Serial.println("WebSocket server started.");
}

// 릴레이 컨트 핀의 상태와 타이머 잔여분을 #으로 구분해서 웹소켓으로 전송
// ex) "0#59" 
void noticeForClient() {
  webSocket.textAll(String(L1Status)+"#"+String(minuteToOff));
}

// 클라이언트에서 오는 웹소켓 메시지를 처리하는 함수
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "toggle") == 0) {       // "toggle"이 전송되면
      L1Status = !L1Status;                         // 릴레이 상태 변수를 전환하고
      minuteToOff = (L1Status == LOW) ? 60 : 0;     // LOW 상태이면 타이머 1시간, 아니면 0으로 설정
    }
    else if (data[0]=='@') {                        // "@"로 시작하는 문자열이 전송되면
      String s = (const char*)&data[1];             // 두번째 문자에서 시작하는 문자열을 추출해서
      minuteToOff = s.toInt();                      // 문자를 정수로 변환하고 타이머 변수에 저장
    }
    digitalWrite(load0, L1Status);                  // 릴레이 상태 변수에 따라 핀 상태 전환
    noticeForClient();                              // 웹소켓 메시지가 오면 무조건 현상태를 회신
  }
}

// 웹소켓 이벤트를 구분하는 함수
void webSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                    void *arg, uint8_t *data, size_t len) { // When a WebSocket message is received
  switch (type) {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}
