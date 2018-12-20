#include <Arduino.h>
#include "main.h"

//Needed to add a comment to test the github thing.

void setup() {
     Serial.begin(9600);
     Serial.println("Robot Booting...");
     Serial.println();

     //MARK: Line Following Array
     init_line_following();
     init_motors();

     init_arm();

     // dropBall();
}

int count = 0;
void loop() {
     update_arm();

     count++;
     if (count == 100) {
          dropBall();
     }
     return;
     printData();
     // delay(700);
     checkState();
     // printDirection();
     startManeuver(); //Power issue!
     // delay(10);
}
