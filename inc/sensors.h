#pragma once

extern int ambientValue;

extern int Receiver_L_Reading;
extern int Receiver_FL_Reading;
extern int Receiver_FR_Reading;
extern int Receiver_R_Reading;

extern int sensorError;

extern bool frontWall;
extern bool leftWall;
extern bool rightWall;

extern int thresholdFront;
extern int thresholdSide;
extern int thresholdUpperFront; // Threshold for when mouse close to front wall detecting side walls

extern int targetLeft;
extern int targetRight;
extern int targetFront;

void readSensors();
void getSensorError();
void printSensors();
void printSensorsAmbient();
void printSensorsRaw();
void detectWalls();