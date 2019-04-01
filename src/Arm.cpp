#include <Arduino.h>
#include "main.h"

int ARM_PIN = 6; //9
int BALL_LASER_READER_PIN = A0;
int BALL_LASER_PIN = 9;
int update_timer = 0;
int update_timer_timeout = 1;

int destination_angle = 10; //Angle to get to
int rotate_step = 10; // 5 degs every update

enum DROP_STAGES { PREPARING_DROP, DROPPING, BACKUP, FIND_LINE, DONE};
DROP_STAGES current_stage = PREPARING_DROP;
int current_stage_time = 0;

Servo armServo;

void init_arm() {
     Serial.println("Initalizing Ping Pong Arm Servo...");

     // pinMode(BALL_LASER_READER_PIN, INPUT);
     // pinMode(BALL_LASER_PIN, OUTPUT);

     // digitalWrite(BALL_LASER_PIN, HIGH); //Turn the laser on

     armServo.attach(ARM_PIN);

     armServo.write(10);
     destination_angle = 10;

     Serial.println("Arm Servo ready.");
}

void dropBall() {
     setLineState(DISABLED);
     current_stage = PREPARING_DROP;
     current_stage_time = 0;
     current_direction = STOP;

     destination_angle = 160;
}

void update_arm() {
     update_servo_position();
     // armServo.write(20);

     if (current_stage != DONE) { current_stage_time++; }
     int current_angle = armServo.read();

     if (current_angle >= 100 && current_angle <= 106) { current_stage = DROPPING; current_stage_time = 0;}
     // if (current_stage == DROPPING && analogRead(BALL_LASER_READER_PIN) < 1000) { //Laser line broke
     if (current_stage == DROPPING && current_stage_time >= 40) {
          Serial.println("Droped Ball, backing up ------");
          current_stage = BACKUP;
          current_stage_time = 0;
          // current_stage = DONE;
     }
     if (current_stage == BACKUP) {
          current_direction = FORWARD; //Reversed in the Drive file
          if (current_stage_time > 14) {
               setLineState(READ_LINE);
               current_stage = FIND_LINE;
               current_stage_time = 0;
          }
          // current_direction = FORWARD;
          // if (current_stage_time > 10 && current_stage_time <= 15) { current_direction = LEFT; }
          // if (current_stage_time > 15) {
               // setLineState(READ_LINE);
               // current_stage = FIND_LINE;
               // current_stage_time = 0;
          // }
     }
     if (current_stage == FIND_LINE && current_stage_time >= 80) {
          current_stage = DONE;
          current_stage_time = 0;
          Serial.println("Competed Dropping Ball");
     }
     if (current_stage == DONE) {
          destination_angle = 10;
     }
}

void update_servo_position() {
     // Serial.print("Servo Update; Angle: ");
     // Serial.println(armServo.read());

     update_timer++;
     if (update_timer <= update_timer_timeout) { return; }
     update_timer = 0;

     int current_angle = armServo.read();

     if (current_angle < destination_angle) { //Add
          if (current_angle + rotate_step <= destination_angle) {
               armServo.write(current_angle + rotate_step);
               return;
          }
          if (current_angle != destination_angle) { armServo.write(destination_angle); }
     }else { //Subtract
          if (current_angle - rotate_step >= destination_angle) {
               armServo.write(current_angle - rotate_step);
               return;
          }
          if (current_angle != destination_angle) { armServo.write(destination_angle); }
     }
}
