#pragma once
#include "../inc/encoders.h"
#include "../inc/sensors.h"
#include <Arduino.h>

extern double accX;
extern double accW;
extern double decX;
extern double decW;

extern double sensorFeedback;
extern double sensor_scale;
extern bool useSensors;

extern double curSpeedX;
extern double curSpeedW;
extern double targetSpeedX;
extern double targetSpeedW;

extern double encoderFeedbackX;
extern double encoderFeedbackW;

extern int outMin;
extern int outMax;

extern double ITermX;
extern double ITermW;

extern double lastSpeedX;
extern double lastSpeedW;

extern double kpX; // Slightly confident this number is good
extern double kpW;
extern double kiX; // Very confident in this number
extern double kiW;
extern double kdX; // Very confident in this number
extern double kdW;

void PID();
void updateCurrentSpeed();