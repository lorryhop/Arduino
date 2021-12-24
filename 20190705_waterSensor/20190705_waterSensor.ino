const int greenLed = 7;
const int yellowLed = 8;
const int waterLevel = 0;

int val;

void setup() {
  // put your setup code here, to run once:
   pinMode(greenLed, OUTPUT);
   pinMode(yellowLed, OUTPUT);

   val = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.begin(9600);

  val = analogRead(waterLevel);   // analogPin 의 변화값(전류값)을 읽음
  Serial.println(val);      // 시리얼모니터에 전류값 표시
  
  if(val > 1000) {                // val 값이 100이 넘으면 (전류가 100이 넘으면)                              
    digitalWrite(yellowLed, HIGH);   // LED ON
  } else {                       // val 값이 100이하면 (전류가 100이하면)
    digitalWrite(yellowLed, LOW);    // LED OFF
  }
  
  digitalWrite(greenLed, HIGH);
  delay(500);
  digitalWrite(greenLed, LOW);
  delay(500);
}
