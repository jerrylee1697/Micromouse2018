#pragma once

extern double distanceLeftX;
extern double distanceLeftW;
extern double accX;
extern double accW;
extern double decX;
extern double decW;
extern double curSpeedX;
extern double curSpeedW;
extern double targetSpeedX;
extern double targetSpeedW;
extern int posPwmX;
extern int posPwmW;
extern double posErrorX;
extern double posErrorW;
extern double oldPosErrorX;
extern double oldPosErrorW;
extern int leftBaseSpeed;
extern int rightBaseSpeed;
extern double encoderFeedbackX;
extern double encoderFeedbackW;
extern double sensorFeedback;
extern double sensor_scale;
extern bool useSensors;
extern double kpX;
extern double kpW;
extern double kdX;
extern double kdW;
// extern volatile bool startingCell = false;
extern int moveSpeed;
extern int turnSpeed;
extern int returnSpeed;
extern int stopSpeed;
extern int maxSpeed;


void setLeftPwm(int);
void setRightPwm(int);
void updateCurrentSpeed();
void calculateMotorPwm();