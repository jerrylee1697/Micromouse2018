#pragma once
#include "../inc/encoders.h"
#include "../inc/macros.h"
#include "../inc/motors.h"
#include <Arduino.h>

extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;

extern volatile int MotorRightForward;
extern volatile int MotorRightReverse;
extern volatile int MotorLeftForward;
extern volatile int MotorLeftReverse;

void PID();

void ResetEncoders();