#pragma once

extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;

void countLeftEncoderA();
void countLeftEncoderB();
void countRightEncoderA();
void countRightEncoderB();

void printEncoders();

void updateEncoderStatus();