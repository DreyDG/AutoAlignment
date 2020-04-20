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

void setup() {
    /*
     * Set target motor RPM.
     */
    stepper.begin(RPM);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    // stepper.setEnableActiveState(LOW);
//    stepper.enable();
    
}

void loop() {
    delay(1000);

    /*
     * Moving motor in full step mode is simple:
     */
//    stepper.setMicrostep(1);  // Set microstep mode to 1:1

    // One complete revolution is 360°
//    stepper.rotate(360);     // forward revolution
//    stepper.rotate(-360);    // reverse revolution

    // One complete revolution is also MOTOR_STEPS steps in full step mode
//    stepper.move(MOTOR_STEPS);    // forward revolution
//    stepper.move(-MOTOR_STEPS);   // reverse revolution

    /*
     * Microstepping mode: 1, 2, 4, 8, 16 or 32 (where supported by driver)
     * Mode 1 is full speed.
     * Mode 32 is 32 microsteps per step.
     * The motor should rotate just as fast (at the set RPM),
     * but movement precision is increased, which may become visually apparent at lower RPMs.
     */
//    stepper.setMicrostep(8);   // Set microstep mode to 1:8

    // In 1:8 microstepping mode, one revolution takes 8 times as many microsteps
//    stepper.move(8 * MOTOR_STEPS);    // forward revolution
//    stepper.move(-8 * MOTOR_STEPS);   // reverse revolution
    
    // One complete revolution is still 360° regardless of microstepping mode
    // rotate() is easier to use than move() when no need to land on precise microstep position
//    stepper.rotate(360);
//    stepper.rotate(-360);

        stepper.setMicrostep(16);   // Set microstep mode to 1:16

    // In 1:8 microstepping mode, one revolution takes 8 times as many microsteps
//    stepper.move(16 * MOTOR_STEPS);    // forward revolution
//    stepper.move(-16 * MOTOR_STEPS);   // reverse revolution
    
    // One complete revolution is still 360° regardless of microstepping mode
    // rotate() is easier to use than move() when no need to land on precise microstep position
//    stepper.rotate(360*2);
    delay(1000);
    
  for(int x = 0; x < (100); x++) {
stepper.rotate(+360);
  }
  
   delay(1000);
   
    for(int x = 0; x < (100); x++) {
stepper.rotate(-360);
    }


}
