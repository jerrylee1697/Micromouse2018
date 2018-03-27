#include "../inc/pid.h"
#include "../inc/pwm.h"
#include "../inc/encoders.h"
#include "../inc/motors.h"
#include <Arduino.h>

int error = 0;

int outMin = -255;	// Limit the motors only because 
int outMax = 255;

double ITermX;
double ITermW;

double lastSpeedX = 0;
double lastSpeedW = 0;

double kpX = .5; // Slightly confident this number is good
double kpW = .5;
double kiX = .2; // Very confident in this number
double kiW = .2;
double kdX = .15; // Very confident in this number
double kdW = .15;

void PID() {
	error = encoderValueRight - encoderValueLeft;
	if (error > 0) {
		MotorRightForward -= error;
	}
	else  if (error < 0) {
		MotorRightForward -= error;
	}
}

void ResetEncoders() {
	encoderValueRight = 0;
	encoderValueLeft = 0;
}

void fuckGreensPID() {
	int rotationalFeedback;

	encoderFeedbackX = rightEncoderChange + leftEncoderChange;
	encoderFeedbackW = rightEncoderChange - leftEncoderChange;   // Positive if mouse rotates CW

	if (useSensors) {
		// sensorFeedback = sensorError/sensor_scale;
	}
	else {
		sensorFeedback = 0;
	}
	rotationalFeedback = encoderFeedbackW - sensorFeedback;

	double errorX = curSpeedX - encoderFeedbackX;
   ITermX += (kiX * errorX);
   if (ITermX > outMax) ITermX = outMax;
   else if (ITermX < outMin) ITermX = outMin;
   double dInputX = (curSpeedX - lastSpeedX);

   double errorW = curSpeedW - rotationalFeedback;
   ITermW += (kiW * errorW);
   if (ITermW > outMax) ITermW = outMax;
   else if (ITermW < outMin) ITermW = outMin;
   double dInputW = (curSpeedW - lastSpeedW);

   lastSpeedX = curSpeedX;
   lastSpeedW = curSpeedW;

	double OutputX, OutputW;

	OutputX = kpX * errorX + ITermX - kdX * dInputX;
	if(OutputX > outMax) OutputX = outMax;
   else if(OutputX < outMin) OutputX = outMin;

   OutputW = kpW * errorW + ITermW - kdW * dInputW;
	if(OutputW > outMax) OutputW = outMax;
   else if(OutputW < outMin) OutputW = outMin;

   // Serial.print(OutputW); // Commanded speed
   // Serial.print(',');
   // Serial.println(encoderFeedbackW); // True speed

	leftBaseSpeed = OutputX - OutputW;
	rightBaseSpeed = OutputX + OutputW;

	setLeftPwm(leftBaseSpeed);
	setRightPwm(rightBaseSpeed);
}