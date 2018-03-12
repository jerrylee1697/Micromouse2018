#pragma once

extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;

extern int leftEncoder;
extern int rightEncoder;

extern double encoderCount;
extern int leftEncoderCount;
extern int rightEncoderCount;

extern double encoderChange;
extern int leftEncoderChange;
extern int rightEncoderChange;

extern double oldEncoderCount;
extern int leftEncoderOld;
extern int rightEncoderOld;

void countLeftEncoderA();
void countLeftEncoderB();
void countRightEncoderA();
void countRightEncoderB();

void printEncoders();

void updateEncoderStatus();