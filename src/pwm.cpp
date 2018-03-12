#include "../inc/pwm.h"
#include "../inc/macros.h"
#include "../inc/encoders.h"
#include <Arduino.h>

double distanceLeftX;
double distanceLeftW;
double accX = 1.5;
double accW = 0.35;
double decX = 1.5;
double decW = 0.35;
double curSpeedX = 0;
double curSpeedW = 0;
double targetSpeedX = 0;
double targetSpeedW = 0;
int posPwmX = 0;
int posPwmW = 0;
double posErrorX = 0;
double posErrorW = 0;
double oldPosErrorX = 0;
double oldPosErrorW = 0;
int leftBaseSpeed = 0;
int rightBaseSpeed = 0;
double encoderFeedbackX = 0;
double encoderFeedbackW = 0;
double sensorFeedback = 0;
double sensor_scale = 50;
bool useSensors = false;
double kpX = .5;
double kpW = .4;
double kdX = 0.05;
double kdW = 0;
// volatile bool startingCell = false;
int moveSpeed = 25;
int turnSpeed = 25;
int returnSpeed = 10;
int stopSpeed = 30;
int maxSpeed = 70;
int antiWindup = 2550;

void setLeftPwm(int speed) {
  if(speed > 255)//parameter check
    speed = 255;
  if(speed < -255)
    speed = -255;

    if(speed >= 0) { //forward
      analogWrite(M1Reverse, 0);
      analogWrite(M1Forward, speed);
    }
    else { //backward
      analogWrite(M1Reverse, -speed);
      analogWrite(M1Forward, 0);
    }
}
void setRightPwm(int speed) {
	if(speed > 255)
		speed = 255;
	if(speed < -255)
		speed = -255;

	if(speed >= 0) { //forward
		analogWrite(M2Reverse, 0);
		analogWrite(M2Forward, speed);
	}
	else { //backward
		analogWrite(M2Reverse, -speed);
		analogWrite(M2Forward, 0);
	}
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
}

void calculateMotorPwm() {
	int rotationalFeedback;

    /* simple PD loop to generate base speed for both motors */
	encoderFeedbackX = rightEncoderChange + leftEncoderChange;
	encoderFeedbackW = rightEncoderChange - leftEncoderChange;   // Positive if mouse rotates CW
	if (useSensors) {
		// sensorFeedback = sensorError/sensor_scale;
	}
	else {
		sensorFeedback = 0;
	}
	if (useSensors) {
		rotationalFeedback = encoderFeedbackW - sensorFeedback;
	}
	else {
		rotationalFeedback = encoderFeedbackW;
	}

	posErrorX += curSpeedX - encoderFeedbackX;
	if (posErrorX > antiWindup) {	// Anti-windup code
		posErrorX = antiWindup;
	}
	else if (posErrorX < -antiWindup) {
		posErrorX = -antiWindup;
	}

	posErrorW += curSpeedW - rotationalFeedback;
	if (posErrorW > antiWindup) {	// Anti-windup code
		posErrorW = antiWindup;
	}
	else if (posErrorW < -antiWindup) {
		posErrorW = -antiWindup;
	}

	posPwmX = kpX * posErrorX - kdX * (posErrorX - oldPosErrorX);
	posPwmW = kpW * posErrorW + kdW * (posErrorW - oldPosErrorW);

	oldPosErrorX = posErrorX;
	oldPosErrorW = posErrorW;

	leftBaseSpeed = posPwmX - posPwmW;
	rightBaseSpeed = posPwmX + posPwmW;

	setLeftPwm(leftBaseSpeed);
	setRightPwm(rightBaseSpeed);
}

// void moveOneCell() {
//   targetSpeedW = 0;
//   targetSpeedX = moveSpeed;

//   do
//   {
//     /*you can call int needToDecelerate(int32_t dist, int16_t curSpd, int16_t endSpd)
//     here with current speed and distanceLeft to decide if you should start to decelerate or not.*/
//     /*sample*/
//     if(needToDecelerate(distanceLeftX, curSpeedX, moveSpeed) < decX)
//       targetSpeedX = maxSpeed;
//     else
//       targetSpeedX = moveSpeed;

//     //there is something else you can add here. Such as detecting falling edge of post to correct longitudinal position of mouse when running in a straight path
//   }
//   while( (encoderCount-oldEncoderCount) < 300);
//   //LFvalues1 and RFvalues1 are the front wall sensor threshold when the center of mouse between the boundary of the cells.
//   //LFvalues2 and RFvalues2 are the front wall sensor threshold when the center of the mouse staying half cell farther than LFvalues1 and 2
//   //and LF/RFvalues2 are usually the threshold to determine if there is a front wall or not. You should probably move this 10mm closer to front wall when collecting
//   //these thresholds just in case the readings are too weak.

//   oldEncoderCount = encoderCount; //update here for next movement to minimized the counts loss between cells.
// }