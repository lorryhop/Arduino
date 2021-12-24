int ledGreen =2;
int ledYellow =6;
int ledRed =4;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
  //핀모드 설정
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  
}
 
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("start");
  
  dou(1000);
  le(1000);
  mi(1000);
  
  Serial.println(" ");
  
  dou(2000);  
  le(2000);
  mi(2000);
  
  Serial.println(" ");
  
  dou(3000);   
  le(3000);
  mi(3000);
  
  Serial.println(" ");
  
  dou(4000);
  le(4000); 
  mi(4000);
  
  Serial.println("END");

  Serial.println(" ");
  Serial.println(" ");
} 

void dou(int sec) {
  //도 구간
  digitalWrite(ledGreen, HIGH);
  Serial.println("도");
    delay(sec);
  digitalWrite(ledGreen, LOW);

}

void le(int sec) {
  //레 구간
  digitalWrite(ledRed, HIGH);
  Serial.println("레");
    delay(sec);
  digitalWrite(ledRed, LOW);

}

void mi(int sec) {
  //미 구간
  digitalWrite(ledYellow,HIGH);
  Serial.println("미");
    delay(sec);
  digitalWrite(ledYellow,LOW);
}

  
