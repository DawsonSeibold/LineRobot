#include <Arduino.h>
#include "main.h"

int ARM_PIN = 9;
int update_timer = 0;
int update_timer_timeout = 1;

int destination_angle = 180; //Angle to get to
int rotate_step = 10; // 5 degs every update

Servo armServo;

void init_arm() {
     Serial.println("Initalizing Ping Pong Arm Servo...");

     armServo.attach(ARM_PIN);

     Serial.println("Arm Servo ready.");
}

void dropBall() {
     Serial.print("destination_angle: ");
     Serial.println(destination_angle);

     Serial.print("current_angle: ");
     Serial.println(armServo.read());

     if (destination_angle == 180) {
          if (armServo.read() == 180) { destination_angle = 0; }
          return;
     }
     if (armServo.read() == 0) { destination_angle = 180; }
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
