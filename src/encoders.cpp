#include "../inc/encoders.h"
#include "../inc/macros.h"
#include "../inc/pwm.h"
#include "../inc/movement.h"
#include <Arduino.h>

volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;

int leftEncoder;
int rightEncoder;

double encoderCountX;
int encoderCountW;
int leftEncoderCount;
int rightEncoderCount;

double encoderChange;
int leftEncoderChange;
int rightEncoderChange;

double oldEncoderCount;
int leftEncoderOld;
int rightEncoderOld;

void countLeftEncoderA() {
	if (digitalRead(EncoderL_A)) {
		if (digitalRead(EncoderL_B)) { // If channel A leads B, CW
			encoderValueLeft--;
		}
		else {
			encoderValueLeft++;
		}
	}
	else {
		if (digitalRead(EncoderL_B)) {
			encoderValueLeft++;
		}
		else {
			encoderValueLeft--;
		}
	}
}

void countLeftEncoderB() {
	if (digitalRead(EncoderL_B)) {
	   	if (digitalRead(EncoderL_A)) {
	   		encoderValueLeft++;
	   	}
		else {
			encoderValueLeft--;
		}
	}
	else {
		if (digitalRead(EncoderL_A)) {
			encoderValueLeft--;
		}
		else {
			encoderValueLeft++;
		}
	}
}

void countRightEncoderA() {
	if (digitalRead(EncoderR_A)) {
		if (digitalRead(EncoderR_B)) { // If channel A leads B, CW
			encoderValueRight--;
		}
		else {
			encoderValueRight++;
		}
	}
	else {
		if (digitalRead(EncoderR_B)) {
			encoderValueRight++;
		}
		else {
			encoderValueRight--;
		}
	}
}

void countRightEncoderB() {
	if (digitalRead(EncoderR_B)) {
		if (digitalRead(EncoderR_A)) {
			encoderValueRight++;
		}
		else {
			encoderValueRight--;
		}
	}
	else {
		if (digitalRead(EncoderR_A)) {
			encoderValueRight--;
		}
		else {
			encoderValueRight++;
		}
	}
}

void printEncoders() {
	Serial.print(encoderValueLeft);
	Serial.print(",");
	Serial.println(encoderValueRight);
}

void updateEncoderStatus() {
	leftEncoder = encoderValueLeft;
	rightEncoder = encoderValueRight;

	leftEncoderChange = leftEncoder - leftEncoderOld;
	rightEncoderChange = rightEncoder - rightEncoderOld;
	encoderChange = (double)(leftEncoderChange + rightEncoderChange)/2;

	leftEncoderOld = leftEncoder;
	rightEncoderOld = rightEncoder;

	leftEncoderCount += leftEncoderChange;
	rightEncoderCount += rightEncoderChange;
	encoderCountX =  (double)(leftEncoderCount+rightEncoderCount)/2;
	encoderCountW = rightEncoderCount - leftEncoderCount;

	distanceLeftX -= encoderChange;
	distanceLeftW -= rightEncoderChange - leftEncoderChange; // distanceLeftW: CW is positive
}