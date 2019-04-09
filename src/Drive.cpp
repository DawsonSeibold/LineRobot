#include <Arduino.h>
#include "main.h"
// #include "Ardumoto.h" ABSTRACTED

Ardumoto Moto;
Directions current_direction = STOP;
Directions last_direction = STOP;

int current_maneuver_time = 0;
int maneuver_time_out = 3;

int SPEED = 200; // 170
int REVERSE_SPEED = 165;
int normal_speed = SPEED; //170

bool passed_start_line = false;
bool stuck_at_start_line = false;
bool heading_to_finish_line = true;
bool is_driving_backwards = false;

int time_to_load_ball = 100;
int time_to_load_ball_passed = 0;
bool is_waiting_for_ball_loading = false;

void init_motors() {
     Serial.println("Seting Up Motors...");

     Moto.begin();

     Serial.println("Motors Setup Complete");
     Serial.println();

     // test_motors();
}


void printDirection() {
     switch (current_direction) {
          case FORWARD:
               Serial.println("FORWARD");
               break;
          case BACK:
               Serial.println("BACK");
               break;
          case LEFT:
               Serial.println("LEFT");
               break;
          case RIGHT:
               Serial.println("RIGHT");
               break;
          case STOP:
               Serial.println("STOP");
               break;
     }
}

void passedHorizontalLines() {
     if (!passed_start_line) { //Just passed the start line on the first trip, (ignore)
          passed_start_line = true;
          Serial.println("Start Line ----------------");
          setLineState(READ_LINE);
          stuck_at_start_line = true;
     }else {
          if (heading_to_finish_line) { //Hit end, drop the ball, start heading backwards
               Serial.println("Finish Line ----------");
               dropBall();
               // is_driving_backwards = true;
               // normal_speed = REVERSE_SPEED;
               heading_to_finish_line = false;
          }else { //Hit start, wait for loading, go forward
               Serial.println("Start Line (2nd)  --------------");
               is_waiting_for_ball_loading = true;
               // is_driving_backwards = false;
               // normal_speed = SPEED;
               heading_to_finish_line = true;

               setLineState(DISABLED);
               current_direction = STOP;
          }
     }
}

void startManeuver() {

     // current_maneuver_time++;
     // if (current_maneuver_time <= maneuver_time_out) {
     //   return;
     // }
     // current_maneuver_time = 0;

     // Serial.print("Current Direction: ");
     // Serial.println(current_direction);


     switch (current_direction) {
          case FORWARD:
               Moto.setSpeed(MotoA, (is_driving_backwards ? -normal_speed : normal_speed));
               Moto.setSpeed(MotoB, (is_driving_backwards ? -normal_speed : normal_speed));
               break;
          case BACK:
               Moto.setSpeed(MotoA, (is_driving_backwards ? 80 : -80));
               Moto.setSpeed(MotoB, (is_driving_backwards ? 80 : -80));
               break;
          case LEFT:
               // if (is_driving_backwards) {//Go Right Instead
               //      Moto.setSpeed(MotoA, normal_speed);
               //      Moto.setSpeed(MotoB, -170);
               // }else {
                    Moto.setSpeed(MotoA, -170);
                    Moto.setSpeed(MotoB, normal_speed);
               // }
          break;
               case RIGHT:
               // if (is_driving_backwards) {//Go Left instead
               //      Moto.setSpeed(MotoA, -170);
               //      Moto.setSpeed(MotoB, normal_speed);
               // }else {
                    Moto.setSpeed(MotoA, normal_speed);
                    Moto.setSpeed(MotoB, -170);
               // }
               break;
          case STOP:
               Moto.stop(MotoA);
               Moto.stop(MotoB);
               break;
     }
}

void checkBallLoadingStatus() {
     time_to_load_ball_passed++;
     // if (analogRead(BALL_LASER_READER_PIN) < 1000) { //Laser line broken
     if (time_to_load_ball_passed >= time_to_load_ball) { //TODO add a laser and photocell to detect when the ball is loaded.
          is_waiting_for_ball_loading = false;
          time_to_load_ball_passed = 0;
          Serial.println("Ball Loading Complete");

          should_turn_around = true;
          setLineState(DISABLED);
          // setLineState(READ_LINE);
          // current_direction = FORWARD;
     }
}

int turn_around_time = 0;
bool should_turn_around = false;

void turnAround() {
     if (should_turn_around == true) {
          turn_around_time++;
          current_direction = BACK;
          if (turn_around_time >= 100 && turn_around_time <= 300) { current_direction = RIGHT; return;}
          if (turn_around_time >= 200 && turn_around_time <= 310) {
               setLineState(READ_LINE);
               turn_around_time = 0;
               should_turn_around = false;
          }
     }else {
          turn_around_time = 0;
     }
}

void test_motors() {
     Moto.setSpeed(MotoA, 150);
     delay(5000);
     Moto.stop(MotoA);
     Moto.setSpeed(MotoA, -150);
     delay(5000);
     Moto.stop(MotoA);
     Moto.setSpeed(MotoB, 150);
     delay(5000);
     Moto.stop(MotoB);
     Moto.setSpeed(MotoB, -150);
     delay(5000);
     Moto.stop(MotoB);
}

//FUNCTIONS:
//Moto.setSpeed(MotoA, fullSpeed);
//Moto.setSpeed(MotoB, fullSpeed);
// Moto.stop(MotoA);
// Moto.stop(MotoB);


//Maybe use, idk yet.
// directions currentDirection = stoped;
// directions lastDirection = stoped;
