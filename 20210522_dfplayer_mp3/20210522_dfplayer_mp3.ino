// DFPlayerMini_Fast - Version: Latest 
#include <DFPlayerMini_Fast.h>

// DFPlayer Mini Mp3 by Makuna - Version: Latest 
#include <DFMiniMp3.h>

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
//
void setup () {
  Serial.begin (9600);
  mp3_set_serial (Serial);  //set Serial for DFPlayer-mini mp3 module 
  delay(1);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (15);
}


//
void loop () {        
  mp3_play (1);//0001.mp3재생
  delay (30000);
  mp3_play (2);//0002.mp3재생
  delay (30000);
}
