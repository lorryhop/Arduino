#include <TM1637Display.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3); //RX, TX


//초음파
const int triggerPin = 12;
const int echoPin = 13;

//7디지트용 포트선언
const int DIO = 8; //DIO핀 FND
const int CLK = 9; //CLK핀 FND


TM1637Display display(CLK, DIO);  // set 4Digit FND

//액비통 높이 관련 상수 선언
const int RUBBER = 1;               //고무 1cm
const int PALETTE = 15;             //팔레트 15cm
const int HALF_TON = 29;            //0.5톤 29cm
const int TON = 52;                 //1톤 52cm
const int ONE_AND_A_HALF_TON = 77;  //1.5톤 77cm
const int TWO_TON = 108;            //2톤 108cm


void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  display.setBrightness(0x0a); //FND 최대 밝기
}


void loop()
{
  long duration = 0L;
  long distance_mm = 0L;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  distance_mm = calcDistance(duration);
  
  display.showNumberDec(distance_mm); //디스플레이
  
  //시리얼 모니터 출력
  Serial.print("distance = ");
  Serial.print(distance_mm);
  Serial.println(" cm");
  
  Serial.print("distance = ");
  Serial.print(distance_mm);
  Serial.println(" cm");


  //wifi
  if(mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  if(Serial.available()) {
    mySerial.write(Serial.read());
  }

  delay(100);
}


long calcDistance(long time)
{
  long l_dis;
  
  l_dis = time/29/2;
  
  return l_dis;
}
