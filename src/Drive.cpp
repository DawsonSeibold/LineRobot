#include <Arduino.h>
#include "main.h"
// #include "Ardumoto.h" ABSTRACTED

// Ardumoto Moto;
Directions current_direction = STOP;
Directions last_direction = STOP;

int normal_speed = 150;

void init_motors() {
     Serial.println("Seting Up Motors...");

     Moto.begin();

     Serial.println("Motors Setup Complete");
     Serial.println();
}


void startManeuver() {
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
