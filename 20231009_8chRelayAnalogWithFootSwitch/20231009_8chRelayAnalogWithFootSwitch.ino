/**
 * 20231014 승철이가 고정에 문제있으니 다시
 * 설치해달라고 함
 * 20231022 현장에서 좌우가 바뀌어서 바꿈
 *
 */


const int RELAYS[5] = {9, 10, 11, 12, 13}; //2,4,5,7,8


int btn0_stat = 1;
int btn1_stat = 1;
int btn2_stat = 1;
int btn3_stat = 1;
int btn4_stat = 1;

int fan_stat = 0;
 

void setup()
{
  Serial.begin(9600);

  pinMode(RELAYS[0], OUTPUT);
  pinMode(RELAYS[1], OUTPUT);
  pinMode(RELAYS[2], OUTPUT);
  pinMode(RELAYS[3], OUTPUT);
  pinMode(RELAYS[4], OUTPUT);

  digitalWrite(RELAYS[0], btn0_stat);
  digitalWrite(RELAYS[1], btn1_stat);
  digitalWrite(RELAYS[2], btn2_stat);
  digitalWrite(RELAYS[3], btn3_stat);
  digitalWrite(RELAYS[4], btn4_stat);
}


void loop()
{
 
  Serial.print("BTN0: " + (String)analogRead(A0) + " / ");
  Serial.print("BTN1: " + (String)analogRead(A1) + " / ");
  Serial.print("BTN2: " + (String)analogRead(A2) + " / ");
  Serial.print("BTN3: " + (String)analogRead(A3) + " / ");
  Serial.print("BTN4: " + (String)analogRead(A4));
  Serial.println("");

/*
  Serial.print("btn0_stat: " + (String)btn0_stat + " / ");
  Serial.print("btn1_stat: " + (String)btn1_stat + " / ");
  Serial.print("btn2_stat: " + (String)btn2_stat + " / ");
  Serial.print("btn3_stat: " + (String)btn3_stat + " / ");
  Serial.print("btn4_stat: " + (String)btn4_stat);
  Serial.println("");Serial.println("");
*/

/*
  if(btn0_stat == 0 || btn1_stat == 0 || btn2_stat == 0 || btn3_stat == 0 || btn4_stat == 0) {
    fan_stat = LOW;
    Serial.print("fan_stat : LOW");
  } else {
    fan_stat = HIGH;
    Serial.print("fan_stat : HIGH");
  }
*/

  if(analogRead(A0) > 0) {
    if(btn0_stat == HIGH) {
      btn0_stat = LOW;
      fan_stat = 0;//팬 off
    } else {
      btn0_stat = HIGH;
      fan_stat = 1;//팬 on
    }

    digitalWrite(RELAYS[4], btn0_stat);//FAN

    delay(100);
  }

  if(analogRead(A1) > 0) {
    if(btn1_stat == HIGH) {
      btn1_stat = LOW;
    } else {
      btn1_stat = HIGH;
    }

    digitalWrite(RELAYS[2], btn1_stat);//L1
    if(fan_stat == 0) {
      digitalWrite(RELAYS[4], btn1_stat);//FAN
    }

    delay(100);
  }

  if(analogRead(A2) > 0) {
    if(btn2_stat == HIGH) {
      btn2_stat = LOW;
    } else {
      btn2_stat = HIGH;
    }

    digitalWrite(RELAYS[3], btn2_stat);//L2
    if(fan_stat == 0) {
      digitalWrite(RELAYS[4], btn2_stat);//FAN
    }

    delay(100);
  }

  if(analogRead(A3) > 0) {
    if(btn3_stat == HIGH) {
      btn3_stat = LOW;
    } else {
      btn3_stat = HIGH;
    }

    digitalWrite(RELAYS[1], btn3_stat);//L1
    if(fan_stat == 0) {
      digitalWrite(RELAYS[4], btn3_stat);//FAN
    }

    delay(100);
  }

  if(analogRead(A4) > 0) {
    if(btn4_stat == HIGH) {
      btn4_stat = LOW;
    } else {
      btn4_stat = HIGH;
    }

    digitalWrite(RELAYS[0], btn4_stat);//L2
    if(fan_stat == 0) {
      digitalWrite(RELAYS[4], btn4_stat);//FAN
    }
    
    delay(100);
  }

  delay(100);
}
