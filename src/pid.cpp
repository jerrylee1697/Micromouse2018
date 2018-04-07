#include "../inc/pid.h"
#include "../inc/pwm.h"
#include "../inc/encoders.h"
#include "../inc/sensors.h"
#include <Arduino.h>

double accX = 0.3;  // Probably no need to change.
double accW = 0.4;
double decX = 0.43; // Do not change. Perfect value
double decW = 0.4;

double sensorFeedback = 0;
double turnFeedback = 0;
double sensor_scale = 25;
double turn_scale = 1;
bool useSensors = true;

double curSpeedX = 0;
double curSpeedW = 0;
double targetSpeedX = 0;
double targetSpeedW = 0;

double encoderFeedbackX = 0;
double encoderFeedbackW = 0;

int outMin = -255;	// Anti-windup
int outMax = 255;

double ITermX;
double ITermW;

double lastSpeedX = 0;
double lastSpeedW = 0;

double kpX = 5;//.5;
double kpW = 8;
double kiX = .1;//.2;
double kiW = .1;
double kdX = .15;
double kdW = 1;

void PID() {
	int rotationalFeedback;

	encoderFeedbackX = rightEncoderChange + leftEncoderChange;
	encoderFeedbackW = rightEncoderChange - leftEncoderChange;   // Positive if mouse rotates CW

	// Serial.print(leftEncoderChange);
	// Serial.print(",");
	// Serial.print(rightEncoderChange);
	// Serial.println();

	if (useSensors) {
		sensorFeedback = sensorError/sensor_scale;
	}
	else {
		sensorFeedback = 0;
	}
	turnFeedback = turnFeedback / turn_scale;
	rotationalFeedback = encoderFeedbackW - sensorFeedback - turnFeedback;
	// Serial.println(rotationalFeedback);

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

void updateCurrentSpeed() {
	if(curSpeedX < targetSpeedX) {
		curSpeedX += accX;
    	if(curSpeedX > targetSpeedX)
      	curSpeedX = targetSpeedX;
	} 
	else if(curSpeedX > targetSpeedX) {
		curSpeedX -= decX;
		if(curSpeedX < targetSpeedX)
			curSpeedX = targetSpeedX;
	}
	if(curSpeedW < targetSpeedW) {
		curSpeedW += accW;
		if(curSpeedW > targetSpeedW)
			curSpeedW = targetSpeedW;
	}
	else if(curSpeedW > targetSpeedW) {
		curSpeedW -= decW;
		if(curSpeedW < targetSpeedW)
			curSpeedW = targetSpeedW;
	}
	// if (targetSpeedX == 0) {
	// 	curSpeedX = 0;
	// }
	// if (targetSpeedW == 0) {
	// 	curSpeedW = 0;
	// }
}

void resetPID() {
	ITermX = 0;
	ITermW = 0;
	lastSpeedX = 0;
	lastSpeedW = 0;
	curSpeedX = 0;
	curSpeedW = 0;
	encoderCountX = 0;
	encoderCountW = 0;
}