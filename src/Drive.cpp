#include <Arduino.h>
#include "main.h"
// #include "Ardumoto.h" ABSTRACTED

// Ardumoto Moto;

void init_motors() {
     Serial.println("Seting Up Motors...");

     Moto.begin();

     Serial.println("Motors Setup Complete");
     Serial.println();
}

//FUNCTIONS:
     //Moto.setSpeed(MotoA, fullSpeed);
     //Moto.setSpeed(MotoB, fullSpeed);
     // Moto.stop(MotoA);
     // Moto.stop(MotoB);


//Maybe use, idk yet.
enum directions {
  left,
  right,
  forward,
  back,
  stoped
};
directions currentDirection = stoped;
directions lastDirection = stoped;
