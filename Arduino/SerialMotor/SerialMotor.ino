/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialEvent
*/
#include <Arduino.h>
#include "A4988.h"

// using a 200-step motor (most common)
#define MOTOR_STEPS 200
#define RPM 120

// configure the pins connected
#define DIR 8
#define STEP 9
 #define MS1 10
 #define MS2 11
 #define MS3 12
 A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);

 
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
      /*
     * Set target motor RPM.
     */
    stepper.begin(RPM);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    // stepper.setEnableActiveState(LOW);
//    stepper.enable();

  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  
  stepper.setMicrostep(16);   // Set microstep mode to 1:16
        
  
  if (stringComplete) {
    Serial.println(inputString);
    if (inputString=="a"){   
//      Serial.println("You printed a");
      for(int x = 0; x < (1); x++) {  //move stepper 360 degrees
      stepper.rotate(+360);}}
    if (inputString=="d"){   
      for(int x = 0; x < (1); x++) {  //move stepper 360 degrees
      stepper.rotate(-360);}}  
//    }
  
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
    else{
      inputString += inChar;
    }
    }
  }
