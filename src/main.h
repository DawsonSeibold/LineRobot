// void test;
#ifndef MAIN_H
#define MAIN_H

// #include "lib/SparkFun_Line_Follower_Array/src/sensorbar.h"
#include "Wire.h"
#include "sensorbar.h"
#include "Ardumoto.h"

//LineArray.cpp ~ Line Following Array Sensor
     extern SensorBar LineSensor;
     void init_line_following();
     void printData();

//Drive.cpp ~ Setup & Control Motors
     // extern SensorBar LineSensor;
     extern Ardumoto Moto;
     void init_motors();

#endif
