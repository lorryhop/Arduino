/**
 * 밟고 있는것을 구현할때 누르고 있는 초로 구분하는것이 아니고
 * 애초에 밟았을때 켜지기 때문에 발을 띠는 동작에 멈추는 것을 구현하면 된다.
 */

#define PIN_RELAY 7

int foot_stat = HIGH; //풋스위치의 현재상태
int flag = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_RELAY, OUTPUT);   //릴레이 신호핀
}

void loop() {
  int sVal = analogRead(A0);

  Serial.println(sVal);

  if(sVal == 0) {
    if(flag == 0) {
      flag = 1;
      foot_stat = !foot_stat;
      Serial.println("if");
    }
    
    delay(100);
  } else {
    if(flag == 1) {
      flag = 0;
      Serial.println("else");
    }

    delay(100);
  }
  
  digitalWrite(PIN_RELAY, foot_stat);

  delay(10);
}



/*
void loop() {
  int sVal = analogRead(A0);

  Serial.println(sVal);

  int previousBtnState = 0;
  int currentBtnState = 0;

  if(previousBtnState == 0 && currentBtnState > 0) {//OnClickDown
    if(foot_stat == HIGH) {
      foot_stat = LOW;
      Serial.println("===================ON");

      foot_count = 0;
    } else {
      foot_stat = HIGH;
      Serial.println("===================OFF");
    }
  }

  Serial.println("previousBtnState : "+(String)previousBtnState);
  Serial.println("currentBtnState : "+(String)currentBtnState);
  
  digitalWrite(PIN_RELAY, foot_stat);

  if(previousBtnState == 0 && currentBtnState == 0) {//밟고있는중의 카운트 세기
      foot_count++;
  }

  if(foot_count > 0) {
    Serial.println("=====foot_count : "+(String)foot_count);
  }

  if(previousBtnState > 0 && currentBtnState == 0 && foot_stat == LOW && foot_count > 5) {
    digitalWrite(PIN_RELAY, LOW);
    Serial.println("===================OFFFFFFFFF");
  }

  delay(500);        // delay in between reads for stability
}
*/
