/*
 * Robert Mitchell 
 * 10/23/2019
 * 
 * Allows for AT commands to be entered in Arduino IDE serial monitor.
 * 
 */

#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3
#define baudrate 38400
#define btvcc 7

String msg;
SoftwareSerial hc05(rxPin ,txPin);
void setup(){
  delay(500);
  pinMode(btvcc, OUTPUT);
  digitalWrite(btvcc, HIGH);
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  Serial.begin(9600);
  hc05.begin(baudrate);
}
void loop(){
  readSerialPort();
  if(msg!="") hc05.println(msg);
  
  if (hc05.available()>0){
    Serial.write(hc05.read());
  }
}

void readSerialPort(){
  msg="";
  while (Serial.available()) {
    delay(10);  
    if (Serial.available() >0) {
      char c = Serial.read();  
      msg += c; 
    }
  }
}
