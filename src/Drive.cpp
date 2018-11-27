#include <Arduino.h>
#include "main.h"
// #include "Ardumoto.h" ABSTRACTED

Ardumoto Moto;
Directions current_direction = STOP;
Directions last_direction = STOP;

int current_maneuver_time = 0;
int maneuver_time_out = 10;

int normal_speed = 150;

void init_motors() {
     Serial.println("Seting Up Motors...");

     Moto.begin();

     Serial.println("Motors Setup Complete");
     Serial.println();
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

void startManeuver() {


  current_maneuver_time++;
  if (current_maneuver_time <= maneuver_time_out) {
    return;
  }
  current_maneuver_time = 0;

  Serial.print("Current Direction: ");
  Serial.println(current_direction);


  switch (current_direction) {
    case FORWARD:
      Moto.setSpeed(MotoA, normal_speed);
      Moto.setSpeed(MotoB, normal_speed);
    break;
    case BACK:
    break;
    case LEFT:
      Moto.setSpeed(MotoA, normal_speed);
      Moto.setSpeed(MotoB, -50);
    break;
    case RIGHT:
      Moto.setSpeed(MotoA, -50);
      Moto.setSpeed(MotoB, normal_speed);
    break;
    case STOP:
      Moto.stop(MotoA);
      Moto.stop(MotoB);
    break;
  }
}

//FUNCTIONS:
     //Moto.setSpeed(MotoA, fullSpeed);
     //Moto.setSpeed(MotoB, fullSpeed);
     // Moto.stop(MotoA);
     // Moto.stop(MotoB);


//Maybe use, idk yet.
// directions currentDirection = stoped;
// directions lastDirection = stoped;
