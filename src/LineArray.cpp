#include <Arduino.h>
#include "main.h"

// Uncomment one of the four lines to match your SX1509's address
//  pin selects. SX1509 breakout defaults to [0:0] (0x3E).
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
//const byte SX1509_ADDRESS = 0x3F;  // SX1509 I2C address (01)
//const byte SX1509_ADDRESS = 0x70;  // SX1509 I2C address (10)
//const byte SX1509_ADDRESS = 0x71;  // SX1509 I2C address (11)

SensorBar LineSensor = SensorBar(SX1509_ADDRESS);

LineStates current_state = IDLE;
// uint8_t current_state;

void init_line_following() {
     //Default: the IR will only be turned on during reads.
     LineSensor.setBarStrobe();
     //Other option: Command to run all the time
     //LineSensor.clearBarStrobe();

     //Default: dark on light
     LineSensor.clearInvertBits();
     //Other option: light line on dark
     //mySensorBar.setInvertBits();

     //Don't forget to call .begin() to get the bar ready.  This configures HW.
     uint8_t returnStatus = LineSensor.begin();
     if(returnStatus) {
   	  Serial.println("sx1509 IC communication OK");
     }else {
   	  Serial.println("sx1509 IC communication FAILED!");
     }
     Serial.println();
}

void printData() {
     Serial.print("Density: ");
     Serial.println(LineSensor.getDensity());

     Serial.print("Position: ");
     Serial.println(LineSensor.getPosition());
}

void getState() {
  return current_state;
}

void checkState() { //LineStates state
  switch (current_state) {
    case IDLE:
      current_direction = STOP;
      current_state = READ_LINE;
    break;
    case READ_LINE:
      if (LineSensor.getDensity() < 7) {
        current_state = GO_FORWARD;
        current_direction = FORWARD;
        if (LineSensor.getPosition() < -50) { current_state = GO_LEFT; current_direction = LEFT; }
        if (LineSensor.getPosition() > 50) { current_state = GO_RIGHT; current_direction = RIGHT; }
      }else {
        current_state = IDLE;
      }
    break;
    case GO_FORWARD:
    break;
    case GO_LEFT:
    break;
    case GO_RIGHT:
    break;
    default: //ALSO STOP CASE
      current_direction = STOP;
    break;
  }
}

void completedMotorManeuver() {
  current_state = READ_LINE;
}
