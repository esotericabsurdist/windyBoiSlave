/*
 * Robert W. Mitchell
 * 
 */

/*
 * Robert Mitchell 
 * 10/23/2019
 * 
 */

#include <SoftwareSerial.h>
#define rxPin 0
#define txPin 1
#define baudrate 38400
const int winchIn = 12;
const int winchOut = 13;
String msg;

SoftwareSerial hc05(rxPin, txPin);

// the setup function runs once when you press reset or power the board
void setup() {
  // Set up relay trigger pins. 
  pinMode(winchIn, OUTPUT);
  pinMode(winchOut, OUTPUT);

  // Initialize Bluetooth HC05 board as per board instructions:
  delay(200);  
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  Serial.begin(9600);
  Serial.println("ENTER AT Commands:");
  hc05.begin(baudrate);
 
}

// the loop function runs over and over again forever
void loop() {
  readSerialPort();
  if(msg!=""){
    hc05.println(msg);
  }
  if (hc05.available()>0){
    Serial.write(hc05.read());
  }
                    
}

void readSerialPort(){
  msg="";
  
  while (Serial.available()) {
    delay(10);  
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      msg += c; // makes the string readString
    }
  }
}
