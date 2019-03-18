#include <Arduino.h>
#include "main.h"

void setup() {
     Serial.begin(9600);
     Serial.println("Robot Booting...");
     Serial.println();

     // hasBall = true;

     //MARK: Line Following Array
     init_line_following();
     init_motors();

     init_arm();

     // dropBall();
}

int count = 0;
void loop() {
     update_arm();

     if (is_waiting_for_ball_loading) {
          checkBallLoadingStatus();
          Serial.println("Waiting For Loading");
     }else {
          // printData();
          checkState();
          startManeuver(); //Power issue!
          Serial.println("Looping");
     }
}
