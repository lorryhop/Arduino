void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int sensor1 = random(0, 1023);
  int sensor2 = random(0, 1023);
  int sensor3 = random(0, 1023);
  
  if(Serial.available()) {
    String data = Serial.readStringUntil(0x0a);//라인피더까지 

    Serial.println("[RECVD]" + data);
  }
  
  Serial.println(String(sensor1));
  

  delay(3000);
}
