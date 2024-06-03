#include <Stepper.h>

// 2048:360도, 1024:180도, 512:90도, 256:45도, 128:22.5도
const int stepsPerRevolution = 256;

// 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
Stepper myStepper(stepsPerRevolution,5,3,4,2);


void setup() {
  //Serial.begin(9600);
  
  myStepper.setSpeed(5);
}

void loop() {
  // 시계 방향으로 한바퀴 회전
  myStepper.step(-stepsPerRevolution);
  delay(5000);
}
