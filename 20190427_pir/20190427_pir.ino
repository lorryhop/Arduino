#define LED_GREEN 2
#define LED_RED 3
#define PIR 8

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(PIR);

  Serial.print("PIR value : ");
  Serial.println(value);
  

  if(value == HIGH) {
    digitalWrite(LED_RED, HIGH);
    delay(1000);
    for(int i = 0; i < 5; i++) {
      digitalWrite(LED_GREEN, HIGH);
      delay(300);
      digitalWrite(LED_GREEN, LOW);
      delay(300);
    }
    digitalWrite(LED_RED, LOW);
  }
  delay(1000);
}
