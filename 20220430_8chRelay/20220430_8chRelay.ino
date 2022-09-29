const int RELAYS[5] = {9, 10, 11, 12, 13}; //2,4,5,7,8

const int BTN1 = 3; //FAN
const int BTN2 = 4; //L2
const int BTN3 = 5; //L1
const int BTN4 = 6; //R1
const int BTN5 = 7; //R2

int rcnt = 5;
int fan_after_sec = 10000;

int fan_stat = 1;
int btn1_stat = 1;
int btn2_stat = 1;
int btn3_stat = 1;
int btn4_stat = 1;
int btn5_stat = 1;
 

void setup()
{
  Serial.begin(9600);

  for(int i = 0; i < rcnt; i++) {
    pinMode(RELAYS[i], OUTPUT);
  }

  for(int i = 0; i < rcnt; i++) {
    digitalWrite(RELAYS[i], HIGH); // HIGH로 해야 릴레이 꺼진 상태(풀업 때문?)
  }

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(BTN4, INPUT_PULLUP);
  pinMode(BTN5, INPUT_PULLUP);
}


void loop()
{
  Serial.print("BTN1: " + (String)digitalRead(BTN1) + " / ");
  Serial.print("BTN2: " + (String)digitalRead(BTN2) + " / ");
  Serial.print("BTN3: " + (String)digitalRead(BTN3) + " / ");
  Serial.print("BTN4: " + (String)digitalRead(BTN4) + " / ");
  Serial.print("BTN5: " + (String)digitalRead(BTN5));
  Serial.println("");

  Serial.print("fan_stat: " + (String)fan_stat + " / ");
  Serial.print("btn1_stat: " + (String)btn1_stat + " / ");
  Serial.print("btn2_stat: " + (String)btn2_stat + " / ");
  Serial.print("btn3_stat: " + (String)btn3_stat + " / ");
  Serial.print("btn4_stat: " + (String)btn4_stat + " / ");
  Serial.print("btn5_stat: " + (String)btn5_stat);
  Serial.println("");Serial.println("");

  if(btn1_stat == 0 || btn2_stat == 0 || btn3_stat == 0 || btn4_stat == 0 || btn5_stat == 0) {
    fan_stat = LOW;
    Serial.print("fan_stat : LOW");
  } else {
    fan_stat = HIGH;
    Serial.print("fan_stat : HIGH");
  }

  if(digitalRead(BTN1) == 0) {
    if(btn1_stat == HIGH) {
      btn1_stat = LOW;
    } else {
      btn1_stat = HIGH;
    }

    //digitalWrite(RELAYS[4], btn1_stat); //버튼상태만 바꿔주고 팬상태는 아래쪽에 이미 바꾸고 있어서 주석처리 한다.

    delay(200);
  }

  if(digitalRead(BTN2) == 0) {
    if(btn2_stat == HIGH) {
      btn2_stat = LOW;
    } else {
      btn2_stat = HIGH;
    }

    digitalWrite(RELAYS[0], btn2_stat);

    if(btn2_stat == HIGH) { // 본기계작동후 팬을 n초간 더 돌리기 위함.
      delay(fan_after_sec);  
    }

    delay(200);
  }

  if(digitalRead(BTN3) == 0) {
    if(btn3_stat == HIGH) {
      btn3_stat = LOW;
    } else {
      btn3_stat = HIGH;
    }

    digitalWrite(RELAYS[1], btn3_stat);

    if(btn3_stat == HIGH) { // 본기계작동후 팬을 n초간 더 돌리기 위함.
      delay(fan_after_sec);  
    }

    delay(200);
  }

  if(digitalRead(BTN4) == 0) {
    if(btn4_stat == HIGH) {
      btn4_stat = LOW;
    } else {
      btn4_stat = HIGH;
    }

    digitalWrite(RELAYS[2], btn4_stat);

    if(btn4_stat == HIGH) { // 본기계작동후 팬을 n초간 더 돌리기 위함.
      delay(fan_after_sec);  
    }

    delay(200);
  }

  if(digitalRead(BTN5) == 0) {
    if(btn5_stat == HIGH) {
      btn5_stat = LOW;
    } else {
      btn5_stat = HIGH;
    }

    digitalWrite(RELAYS[3], btn5_stat);

    if(btn4_stat == HIGH) { // 본기계작동후 팬을 n초간 더 돌리기 위함.
      delay(fan_after_sec);  
    }

    delay(200);
  }

/*

  if(fan_stat == HIGH) {
    delay(5000);
  }

*/

  digitalWrite(RELAYS[4], fan_stat); // FAN

  delay(200);
}
