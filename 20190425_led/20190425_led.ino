int ledGreen = 2;
int ledRed = 3;
int sound = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(sound, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);
  delay(1000);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, HIGH);
  delay(1000);

}
