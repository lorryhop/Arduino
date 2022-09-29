
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Hash.h>

#define led1 D3
#define led2 D4
#define led3 D5
#define led4 D6

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

//웹서버의 포트는 기본 포트인 80번을 사용한다!
ESP8266WebServer server(80);
//웹서버와 웹클라이언트가 뒷구멍으로 주고받는 데이터는 웹소켓에서 81번을 쓴다!
WebSocketsServer webSocket = WebSocketsServer(81);

const char* ssid = "SH_SSID";
const char* password = "lorryhop";


String response = "\
<html>\
<head>\
<meta name=\"viewport\" content=\"width=device-width\">\
<meta charset=\"utf-8\">\
<script>\
  var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);\
  connection.onopen = function () {\
     connection.send('Connect ' + new Date());\
  };\
  connection.onerror = function (error) {\
     console.log('WebSocket Error ', error);\
  };\
  connection.onmessage = function (e) {\
     console.log('Server: ', e.data);\
     var recv = JSON.parse(e.data);\
     if(recv.led == 1) document.getElementById('led1').checked = recv.state;\
     else if(recv.led == 2)document.getElementById('led2').checked = recv.state;\
     else if(recv.led == 3)document.getElementById('led3').checked = recv.state;\
     else if(recv.led == 4)document.getElementById('led4').checked = recv.state;\
  };\
  function send_msg(num){\
     if(num == 1){\
        var data = {\
            led:num,\
            state:document.getElementById('led1').checked\
        };\
        connection.send(JSON.stringify(data));\
     }else if(num == 2){\
        var data = {\
            led:num,\
            state:document.getElementById('led2').checked\
        };\
        connection.send(JSON.stringify(data));\
     }else if(num == 3){\
        var data = {\
            led:num,\
            state:document.getElementById('led3').checked\
        };\
        connection.send(JSON.stringify(data));\
     }else if(num == 4){\
        var data = {\
            led:num,\
            state:document.getElementById('led4').checked\
        };\
        connection.send(JSON.stringify(data));\
     }\
  }\
</script>\
</head>\
<body>\
웹소켓을 사용한 예제입니다!<BR>\
LED1<input id=led1 type=checkbox onchange=\"send_msg(1)\"><BR>\
LED2<input id=led2 type=checkbox onchange=\"send_msg(2)\"><BR>\
LED3<input id=led3 type=checkbox onchange=\"send_msg(3)\"><BR>\
LED4<input id=led4 type=checkbox onchange=\"send_msg(4)\"><BR>\
</body>\
</html>";

//클라이언트에서 서버쪽으로 값이 전송되었을때 뭘할거냐?
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            USE_SERIAL.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
            //클라이언트가 접속하면 LED 4개의 상태를 전송한다

            if(digitalRead(led1)) webSocket.sendTXT(num, "{\"led\":1,\"state\":true}");
            else webSocket.sendTXT(num, "{\"led\":1,\"state\":false}");
            if(digitalRead(led2)) webSocket.sendTXT(num, "{\"led\":2,\"state\":true}");
            else webSocket.sendTXT(num, "{\"led\":2,\"state\":false}");
            if(digitalRead(led3)) webSocket.sendTXT(num, "{\"led\":3,\"state\":true}");
            else webSocket.sendTXT(num, "{\"led\":3,\"state\":false}");
            if(digitalRead(led4)) webSocket.sendTXT(num, "{\"led\":4,\"state\":true}");
            else webSocket.sendTXT(num, "{\"led\":4,\"state\":false}");
            
            //num = 소켓번호(클라이언트번호)
            //webSocket.sendTXT(num, "Connected");
        }
            break;
        case WStype_TEXT:
        //메시지 수신부
            USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);
            String msg = "";
            for(int i = 0 ;i<length;i++){
              msg += (char)payload[i];
            }
            webSocket.broadcastTXT(msg);
            //클라이언트에서 온 메시지의 압축을 푼다
            StaticJsonDocument<64> doc;
            deserializeJson(doc, msg);
            int led = doc["led"]; // 1
            bool state = doc["state"]; // true == HIGH, false == LOW
            if(led == 1) digitalWrite(led1,state);
            else if(led == 2) digitalWrite(led2,state);
            else if(led == 3) digitalWrite(led3,state);
            else if(led == 4) digitalWrite(led4,state);
            break;
    }

}

void setup() {
    USE_SERIAL.begin(115200);

    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(led3,OUTPUT);
    pinMode(led4,OUTPUT);
   
    //USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    //자기자신의 IP공유기 ID비밀번호 집어넣는곳!
    WiFiMulti.addAP(ssid, password);

    while(WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
    }

    //IP공유기로부터 할당받은 IP주소를 여기서 출력한다!
    USE_SERIAL.println("IP address: ");
    USE_SERIAL.println(WiFi.localIP());
  
    //웹소켓 서버를 연다
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    //윈도우10, 안드로이드 안됨..의미없는 기능
    if(MDNS.begin("esp8266")) {
        USE_SERIAL.println("MDNS responder started");
    }

    //웹서버의 index.html
    //웹서버가 클라이언트에게 response해주는 부분!

    server.on("/", []() {
        server.send(200, "text/html", response);
    });

    server.begin();

    // Add service to MDNS
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("ws", "tcp", 81);
}

unsigned long last_10sec = 0;
unsigned int counter = 0;

void loop() {
    unsigned long t = millis();
    webSocket.loop(); //이거 있어야한다!
    server.handleClient(); //이거도 있어야한다!

    //delay(~~~~) 절때 쓰면 안됨!

    //10초간격으로 뭔가 하겠다~
    
    if((t - last_10sec) > 1000) {
      last_10sec = millis();
      String msg = "현재 사물인터넷보드의 시간="+String(millis());
      webSocket.broadcastTXT(msg); //모든클라이언트에게 메시지 전송!
    }
}
