
/*
keivn's arduino project
*/

int tones[] = {261, 277, 294, 311, 330, 349, 370, 392};

void setup() {
    Serial.begin(9600);
    
    Serial.println("#### SETUP ####");
    
    pinMode(3, OUTPUT); // 피에조부저
    
    pinMode(7, OUTPUT); // LED
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    
    pinMode(11, INPUT); // 초음파 센서 사용 핀
    pinMode(12, OUTPUT);

}

void loop() {
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);
  
  long distance = pulseIn(11, HIGH)/58.2;

  Serial.println(distance); 
  
  delay(300);
  
  
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
    
  digitalWrite(3, LOW);
    
  if(distance < 100) {
    //digitalWrite(7, HIGH);
    //digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    delay(300);
    digitalWrite(9, LOW);
    //digitalWrite(3, HIGH);
  }

    //7:yellow       8:red     9:green
    //      1              0          0
    //      0              1          0
    //      0              0          1
    //      0              0          0
   /* 
  for(int j= 0; j < 3; j++) {
    Serial.println("YELLOW"); 
    digitalWrite(7, LOW);      //7번 핀에 전기신호를 줌
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    
    
    Serial.println("Init");
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW); 
    
  }
  
  Serial.println("RED");
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);      //8번 핀에 전기신호를 줌
  digitalWrite(9, LOW);
  delay(10);

  Serial.println("GREEN");
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);      //9번 핀에 전기신호를 줌
  
  
  Serial.println("Init");
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);      //9번 핀에 전기신호를 줌
  */
}
