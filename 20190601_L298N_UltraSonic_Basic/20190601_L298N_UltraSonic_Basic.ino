/*  L298N 모터 모듈을 활용한 초음파 센서 제어 회로 */
int distance;             
int triggerPin = 13;
int echoPin = 12;

#define IN1 8  // L298모듈의 제어 신호 입력 핀 번호 지정
#define IN2 9
#define IN3 10
#define IN4 11

void forward() {      // L298 제어용 전진 함수
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);    }
void back() {         // 후진 
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);   }
void left() {         // 좌회전(왼쪽모터 멈춤:오른쪽모터 전진)
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);  }
void right() {      // 우회전(왼쪽모터 전진:오른쪽모터 멈춤)
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);   }
void stop() {       // 정지
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);  }
      
void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);  // 트리거 핀을 출력으로 설정
  pinMode(echoPin, INPUT);      // 에코 핀을 입력으로 설정
  }  
  
void loop() {   
    forward();
    delay(3000);
    back();
    delay(3000);
    right();
    delay(2000);
    left();
    delay(2000);
    stop();
    delay(5000);
  /*digitalWrite(triggerPin, HIGH); // 트리거핀으로 10us의 펄스 발생
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);  //에코 핀의 값을 cm 단위로 계산
  distance = pulseIn(echoPin, HIGH) / 58;   
  distance = distance>100? 100:distance; // 100cm 이상은 모두 100cm로 처리
  Serial.println("Distance(cm) = " + String(distance));
  if (distance < 20) {    // 20cm 이내 장애물 감지
    stop();
    delay(1000);    // 1초간 정지후 후진 
    back();
    delay(2000);    // 2초간 대기
  } else {          //   20cm이내에 벽이 없다면 전진
    forward();     
    }  */
}  
