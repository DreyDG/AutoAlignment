// This is very similar to Example 3 - Receive with start- and end-markers
//    in Serial Input Basics   http://forum.arduino.cc/index.php?topic=396450.0



//motorsetup
#include <Arduino.h>
#include "A4988.h"

// using a 200-step motor (most common)
#define MOTOR_STEPS 200
#define RPM 60

// configure the pins connected
#define DIR 8
#define STEP 9
#define MS1 10
#define MS2 11
#define MS3 12
A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);

const byte numChars = 64;
char receivedChars[numChars];

boolean newData = false;

//byte ledPin = 13;   // the onboard LED

//===============

void setup() {
    Serial.begin(115200);
    stepper.begin(RPM);
//    pinMode(ledPin, OUTPUT);
//    digitalWrite(ledPin, HIGH);
//    delay(200);
//    digitalWrite(ledPin, LOW);
//    delay(200);
//    digitalWrite(ledPin, HIGH);

    Serial.println("<Arduino is ready>");

    stepper.begin(RPM);
}

//===============

void loop() {
    stepper.setMicrostep(16);   // Set microstep mode to 1:16
    recvWithStartEndMarkers();
    replyToPython();
    delay(1000);
    stepmotor();
    delay(1000);
//    stepper.rotate(+360); 
//        delay(1000);
    
}

//===============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//===============

void replyToPython() {
    if (newData == true) {
        Serial.print("<This just in ... ");
        Serial.print(receivedChars);
        Serial.print("   ");
        Serial.print(millis());
        Serial.print('>');
            // change the state of the LED everytime a reply is sent
//        digitalWrite(ledPin, ! digitalRead(ledPin));
        newData = false;
    }
}

void stepmotor(){
//        stepper.rotate(+180);
      if (!strcmp(receivedChars, "a")){
      //move stepper 360 degrees
//      printf("this should work");
      stepper.rotate(+180);  
//        Serial.print("<Stepper moved! ");
//        Serial.print(receivedChars);
//        Serial.print("   ");
//        Serial.print(millis());
//        Serial.print('>');
      }
}
//===============
