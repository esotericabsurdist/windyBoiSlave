/**
 * Robert Mitchell
 * 
 * Program turns powers on HC05 BlueTooth Master/Slave unit configured as Slave
 * and listens for data on its TX pin. 
 * 
 * Depending on character recieved, loop() exclusively toggles two digital pins for relay 
 * control of DC winch motor. Relays are switched on for a fixed time before reading 
 * the next input.
 */

#define btvcc 7
#define winchIn 11
#define winchOut 12
String msg;


void setup() {
  // Set up winch control pins.
  // NOTICE: HIGH is used in place of LOW. 
  //For unknown reasons, this board's digital pins are 0V for HIGH and 5V for LOW. This may be indicative of a problem on the board. 
  digitalWrite(winchIn, HIGH);
  digitalWrite(winchOut, HIGH);
  pinMode(winchIn, OUTPUT);
  pinMode(winchOut, OUTPUT);
  
  // Give everything a little time for soft start up.
  delay(1000);

  // Turn on BlueTooth and set baud rate for reading winch commands.
  pinMode(btvcc, OUTPUT);
  digitalWrite(btvcc, HIGH); // For unknown reasons this pin operates normally. HIGH corresponds to 5V, LOW to 0V.
  Serial.begin(9600); // HC05 is configured out of the box to run at 9600 for transparent mode.
}

void loop() {
  delay(100); // Run Winch for 10th of a second before checking for next instruction.
  if (Serial.available()) {
    char recievedData = Serial.read(); // Read any character found. 
    if (recievedData == 'i') {
      // IN
      digitalWrite(winchIn, HIGH);
      digitalWrite(winchOut, LOW);
    } else if (recievedData == 'o') {
      // OUT
      digitalWrite(winchIn, LOW);
      digitalWrite(winchOut, HIGH);
    }
    else {
      // TURN WINCH OFF, We have an uknown character. 
      digitalWrite(winchIn, HIGH);
      digitalWrite(winchOut, HIGH);
    }
  } else {
    // 
    digitalWrite(winchIn, HIGH);
    digitalWrite(winchOut, HIGH);
  }
}
