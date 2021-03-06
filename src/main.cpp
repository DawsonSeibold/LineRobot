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
     // getServoPosition();
     // armServo.write(0);
     // delay(2000);
     // armServo.write(180);
     // delay(2000);
     // return;

     update_arm();
     turnAround();

     if (is_waiting_for_ball_loading) {
          checkBallLoadingStatus();
          Serial.println("Waiting For Loading");
     }else {
          // printData();
          checkState();
          startManeuver(); //Power issue!
          // Serial.println("L ooping");
     }
}
