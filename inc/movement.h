#pragma once

extern int moveSpeed;
extern int turnSpeed;
extern int returnSpeed;
extern int stopSpeed;
extern int maxSpeed;

extern double distanceLeftX;
extern double distanceLeftW;

double needToDecelerate(int, double, double);
void moveOneCell();