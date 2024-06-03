const int RELAYS[3] = {3, 9, 13};

const int pin_btn0 = 2;   //FAN
const int pin_btn1 = 8;   //M1
const int pin_btn2 = 12;  //M2

int rcnt = 3;
int delay_fan_sec = 5000;

int mtr0_stat = LOW; //fan
int mtr1_stat = LOW;
int mtr2_stat = LOW;

int btn1_flag = 0;
int btn2_flag = 0;

unsigned long currMillis = millis();

void setup()
{
  Serial.begin(9600);

  for(int i = 0; i < rcnt; i++) {
    pinMode(RELAYS[i], OUTPUT);
  }

  for(int i = 0; i < rcnt; i++) {
    digitalWrite(RELAYS[i], LOW); // HIGH로 해야 릴레이 꺼진 상태(풀업 때문?)
  }

  pinMode(pin_btn0, INPUT_PULLUP);
  pinMode(pin_btn1, INPUT_PULLUP);
  pinMode(pin_btn2, INPUT_PULLUP);

  //curr_millis = millis();
}


void loop()
{
  unsigned long currMillis = millis();
  
  Serial.print("pin_btn0: " + (String)digitalRead(pin_btn0) + " / ");
  Serial.print("pin_btn1: " + (String)digitalRead(pin_btn1) + " / ");
  Serial.print("pin_btn2: " + (String)digitalRead(pin_btn2));
  Serial.println("");Serial.println("");

  Serial.print("mtr0_stat: " + (String)mtr0_stat + " / ");
  Serial.print("mtr1_stat: " + (String)mtr1_stat + " / ");
  Serial.print("mtr2_stat: " + (String)mtr2_stat);
  Serial.println("");Serial.println("");

  if(digitalRead(pin_btn0) == 0) {
    if(mtr0_stat == HIGH) {
      mtr0_stat = LOW;
    } else {
      mtr0_stat = HIGH;
    }
  }

  if(digitalRead(pin_btn1) == 0) {
    if(mtr1_stat == HIGH) {
      mtr1_stat = LOW;
    } else {
      mtr1_stat = HIGH;
    }
  }

  if(digitalRead(pin_btn2) == 0) {
    if(mtr2_stat == HIGH) {
      mtr2_stat = LOW;
    } else {
      mtr2_stat = HIGH;
    }
  }

  digitalWrite(RELAYS[1], mtr1_stat);
  digitalWrite(RELAYS[2], mtr2_stat);
  if(mtr0_stat == HIGH || mtr1_stat == HIGH || mtr2_stat == HIGH) {
    digitalWrite(RELAYS[0], HIGH); // FAN
  } else {
    digitalWrite(RELAYS[0], LOW); // FAN  
  }
  
  delay(300);
}
