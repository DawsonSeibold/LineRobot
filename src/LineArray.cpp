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

int lost_timer = 0;
int start_delay = 30;
int start_delay_timer = 0;

bool horizontal_lines_cooldowned = true;

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
     // Serial.print("Density: ");
     Serial.println(LineSensor.getDensity());

     Serial.print("Position: ");
     Serial.println(LineSensor.getPosition());

     Serial.println("----------------------------------");
     // Serial.print("Direction: ");
     // Serial.println(current_direction);
}

void getState() {
     return;
     // return current_state;
}

int counter = 0;
void checkState() { //LineStates state
     start_delay_timer++;

     uint8_t density = LineSensor.getDensity();
     int8_t position = LineSensor.getPosition();

     switch (current_state) {
          case DISABLED:
          break;
     case IDLE:
          Serial.println("IDLE");
          current_direction = STOP;
          current_state = READ_LINE;
          break;
     case READ_LINE:
          lost_timer = 0;
          Serial.println("READ_LINE");

          if (density <= 7 && density >= 1) {
               horizontal_lines_cooldowned = true;
               if (position < -50) { current_state = GO_RIGHT; current_direction = RIGHT; return; }
               if (position > 50) { current_state = GO_LEFT; current_direction = LEFT; return; }
               // if (LineSensor.getPosition() > -50 && LineSensor.getPosition() < 50) { current_state = GO_FORWARD; current_direction = FORWARD; return;}
               current_state = GO_FORWARD;
               current_direction = FORWARD;
               stuck_at_start_line = false;
               // Serial.println("Set to forward");
          }else if (density >= 6) { //SOLID LINE FOUND - ALL BLACK
               if (horizontal_lines_cooldowned) {
                    Serial.println("ALL BLACK");
                    passedHorizontalLines();
                    horizontal_lines_cooldowned = false;
               }else {
                    if (stuck_at_start_line) {
                         current_state = GO_FORWARD;
                         current_direction = FORWARD;
                    }
               }
               // if (start_delay_timer >= start_delay && horizontal_lines_cooldowned == true) { Serial.println("ALL BLACK"); passedHorizontalLines(); horizontal_lines_cooldowned = false; } //{ dropBall(); }
          }else { // NO LINE FOUND
               current_state = SEARCHING_FOR_LINE;
               // current_direction = BACK;
               current_direction = FORWARD;
          }
          break;
     case SEARCHING_FOR_LINE:
          lost_timer++;

          if (density > 0) { current_state = READ_LINE; }
          if (lost_timer < 5) { current_direction = FORWARD; return; }
          if (lost_timer < 15) { current_direction = BACK; return; }
          if (lost_timer < 25) {current_direction = LEFT; return; }
          if (lost_timer < 65) { current_direction = RIGHT; return; }
          current_direction = STOP;
          break;
     case GO_FORWARD:
          // Serial.println("GO_FORWARD");
          current_state = READ_LINE;
          break;
     case GO_LEFT:
          // Serial.println("GO_LEFT");
          current_state = READ_LINE;
          break;
     case GO_RIGHT:
          // Serial.println("GO_RIGHT");
          current_state = READ_LINE;
          break;
     default: //ALSO STOP CASE
          Serial.println("STOP");
          current_direction = STOP;
          current_state = READ_LINE;
          break;
     }
}

void completedMotorManeuver() {
     current_state = READ_LINE;
}

void setLineState(LineStates new_state) {
     current_state = new_state;
}
