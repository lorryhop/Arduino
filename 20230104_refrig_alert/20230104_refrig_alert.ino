/*
 * 냉장고 온도 경보
 * 나노보드의 경우 툴-프로세서-atmega(old bootloader)로 설정했다
 * 스피커소리가 끊기는 경우 아두이노 reset 버튼을 눌러서 해결한다.
*/

#include <Wire.h>
#include <TM1637Display.h>
#include <DallasTemperature.h>


// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 10
// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);


//릴레이 신호핀
const int relayPin = 8;

long temp = 0.0;

//7디지트용 포트선언
const int DIO = 5;
const int CLK = 6;

TM1637Display display(CLK, DIO);

void setup() 
{
  Serial.begin(9600);

  display.setBrightness(0x0a); //set the diplay to maximum brightness

  pinMode(relayPin, OUTPUT);   //220V 릴레이 신호핀
}


void loop() 
{
 // Send the command to get temperatures
  sensors.requestTemperatures(); 

  temp = sensors.getTempCByIndex(0);
  
  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.println(temp);
  //Serial.print((char)176);//shows degrees character
  
  if(temp > -12) {
    Serial.println("ALERT!!");
    digitalWrite(relayPin, LOW);   // 220V 릴레이 닫힘(ON)  
    display.showNumberDec(temp); //Display the numCounter value;
  } else {
    digitalWrite(relayPin, HIGH);   // 220V 릴레이 닫힘(ON)
    display.showNumberDec(temp); //Display the numCounter value;
  }
  
  delay(500);
}
