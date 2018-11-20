#include <Arduino.h>
#include "main.h"

void setup() {
     Serial.begin(9600);
     Serial.println("Robot Booting...");
     Serial.println();

     //MARK: Line Following Array
     init_line_following();
     init_motors();
}

void loop() {
     printData();
     delay(1000);
}
