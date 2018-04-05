#pragma once

extern int moveSpeed;
extern int turnSpeed;
extern int returnSpeed;
extern int stopSpeed;
extern int maxSpeed;

extern double distanceLeftX;
extern double distanceLeftW;

extern int oneCellDistance;
extern int oneTurnDistance;

double needToDecelerate(int, double, double);
void moveOneCell();
void Forward();
void turnLeft();
void turnRight();
void turnAround();