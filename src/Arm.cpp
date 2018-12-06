#include <Arduino.h>
#include "main.h"

int ARM_PIN = 9;
int update_timer = 0;
int update_timer_timeout = 1;

int destination_angle = 180; //Angle to get to
int rotate_step = 10; // 5 degs every update

enum DROP_STAGES { PREPARING_DROP, DROPPING, BACKUP, FIND_LINE, DONE};
DROP_STAGES current_stage = PREPARING_DROP;
int current_stage_time = 0;

Servo armServo;

void init_arm() {
     Serial.println("Initalizing Ping Pong Arm Servo...");

     armServo.attach(ARM_PIN);

     armServo.write(0);

     Serial.println("Arm Servo ready.");
}

void dropBall() {
     setLineState(DISABLED);
     current_stage = PREPARING_DROP;
     current_stage_time = 0;
     current_direction = STOP;

     destination_angle = 180;
}

void update_arm() {
     update_servo_position();

     current_stage_time++;
     int current_angle = armServo.read();

     Serial.print("Stage Timer: ");
     Serial.println(current_stage_time);

     if (current_angle >= 100 && current_angle <= 106) { current_stage = DROPPING; current_stage_time = 0;}
     if (current_stage == DROPPING && current_stage_time >= 40) {
          current_stage = BACKUP;
          current_stage_time = 0;
     }
     if (current_stage == BACKUP) {
          if (current_stage_time <= 10) { current_direction = BACK; }
          if (current_stage_time > 10 && current_stage_time <= 20) { current_direction = LEFT; }
          if (current_stage_time > 20) {
               setLineState(READ_LINE);
               current_stage = FIND_LINE;
               current_stage_time = 0;
          }
     }
     if (current_stage == FIND_LINE && current_stage_time >= 80) {
          destination_angle = 0;
          current_stage = DONE;
          current_stage_time = 0;
     }
}

void update_servo_position() {

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
