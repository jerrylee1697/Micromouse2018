#pragma once

extern int ambientValue;

extern int Receiver_L_Reading;
extern int Receiver_FL_Reading;
extern int Receiver_FR_Reading;
extern int Receiver_R_Reading;

extern int sensorError;

void readSensors();
void printSensors();
void printSensorsAmbient();
void printSensorsRaw();