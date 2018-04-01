#include "../inc/movement.h"
#include "../inc/encoders.h"
#include "../inc/pid.h"
#include <math.h>
#include <Arduino.h>

int moveSpeed = 10;
int turnSpeed = 15;
int returnSpeed = 10;
int stopSpeed = 30;
int maxSpeed = 67; //62 with pretty low battery

double distanceLeftX;
double distanceLeftW;

int oneCellDistance = 520;
int oneTurnDistance = 340;

double needToDecelerate(int dist, double curSpd, double endSpd) { //speed are in encoder counts/ms, dist is in encoder counts 
	if (curSpd<0) curSpd = -curSpd;
	if (endSpd<0) endSpd = -endSpd;
	if (dist<0) dist = 1;
	if (dist == 0) dist = 1;  //prevent divide by 0

	return (abs(curSpd*curSpd - endSpd*endSpd)/dist/4/2);
	//calculate deceleration rate needed with input distance, input current speed and input targetspeed to determind if the deceleration is needed
	//use equation 2*a*S = Vt^2 - V0^2  ==>  a = (Vt^2-V0^2)/2/S
	//because the speed is the sum of left and right wheels(which means it's doubled), that's why there is a "/4" in equation since the square of 2 is 4
}

void moveOneCell() {
	targetSpeedW = 0;
	targetSpeedX = moveSpeed;
	distanceLeftX = oneCellDistance;
	elapsedMillis wait;
	do {
		/*you can call int needToDecelerate(int32_t dist, int16_t curSpd, int16_t endSpd)
		here with current speed and distanceLeft to decide if you should start to decelerate or not.*/
		if(needToDecelerate(distanceLeftX, curSpeedX, 0) < decX)
			targetSpeedX = moveSpeed;
		else
			targetSpeedX = 0;
		if (wait > 5) {
			// Serial.println(needToDecelerate(distanceLeftX, curSpeedX, moveSpeed));
			// Serial.println(encoderCountX-oldEncoderCount);
			// Serial.println("In Loop");
			wait = 0;
		}
		//there is something else you can add here. Such as detecting falling edge of post to correct longitudinal position of mouse when running in a straight path
		delay(1);
	}
	while( ((encoderCountX-oldEncoderCount) < oneCellDistance && 
		Receiver_L_Reading < targetFront2 && Receiver_R_Reading < targetFront2)	// If no wall in front, use encoders
		|| (Receiver_L_Reading < targetFront && Receiver_L_Reading > targetFront2)
		|| (Receiver_R_Reading < targetFront && Receiver_R_Reading > targetFront2) // If has front wall, use sensors
		 );
	//LFvalues1 and RFvalues1 are the front wall sensor threshold when the center of mouse between the boundary of the cells.
	//LFvalues2 and RFvalues2 are the front wall sensor threshold when the center of the mouse staying half cell farther than LFvalues1 and 2
	//and LF/RFvalues2 are usually the threshold to determine if there is a front wall or not. You should probably move this 10mm closer to front wall when collecting
	//these thresholds just in case the readings are too weak.
	// Serial.println(frontWall);

	if (frontWall) {
		while (Receiver_L_Reading < 350) {
			targetSpeedX = 5;
			delay(1);
		}
		targetSpeedX = 0;
	}

	delay(500);
	oldEncoderCount = encoderCountX; //update here for next movement to minimized the counts loss between cells.
}

void turnLeft() {
	targetSpeedX = 0;
	useSensors = false;
	elapsedMillis wait;
	distanceLeftW = oneTurnDistance;
	while (distanceLeftW > 0) {
		targetSpeedW = turnSpeed;
		delay(5);
		// Serial.println(targetSpeedW);
	}
	turnFeedback = 0;
	targetSpeedW = 0;
	delay(500);
	useSensors = true;
	wait = 0;
	// if (frontWall) {
	// 	while (wait < 500) {
	// 		if (Receiver_L_Reading < 350 && Receiver_R_Reading < 350)
	// 			targetSpeedX = 5;
	// 		if (Receiver_L_Reading > 350 && Receiver_R_Reading > 350)
	// 			targetSpeedX = -5;
	// 		delay(1);
	// 	}
	// 	targetSpeedX = 0;
	// }
	// delay(500);
	resetPID();
}


void turnRight() {
	targetSpeedX = 0;
	useSensors = false;
	elapsedMillis wait;
	distanceLeftW = -oneTurnDistance;
	while (distanceLeftW < 0) {
		targetSpeedW = -turnSpeed;
		delay(5);
		// Serial.println(targetSpeedW);
	}
	turnFeedback = 0;
	targetSpeedW = 0;
	delay(500);
	useSensors = true;
}

void Forward() {
	targetSpeedW = 0;
	targetSpeedX = moveSpeed;
	distanceLeftX = 300;
	do {
		if (Receiver_L_Reading > targetFront || Receiver_R_Reading > targetFront) {
			if(needToDecelerate(300, curSpeedX, 0) < decX) {
				targetSpeedX = moveSpeed;
			}
			else {
				targetSpeedX = 0;
			}
		} 
		else {
			if(needToDecelerate(distanceLeftX, curSpeedX, moveSpeed) < decX)
				targetSpeedX = maxSpeed;
			else
				targetSpeedX = moveSpeed;
		}
	}
	while ( (encoderCountX-oldEncoderCount) < 900);
	oldEncoderCount = encoderCountX;
}