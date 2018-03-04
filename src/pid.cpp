#include "../inc/pid.h"

extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;

extern volatile int MotorRightForward;
extern volatile int MotorRightReverse;
extern volatile int MotorLeftForward;
extern volatile int MotorLeftReverse;

int error = 0;

void PID() {
	error = encoderValueRight - encoderValueLeft;
	if (error > 0) {
		MotorRightForward -= error;
	}
	else  if (error < 0) {
		MotorRightForward -= error;
	}
	// encoderValueLeft = 0;
	// encoderValueRight = 0;
}

void ResetEncoders() {
	encoderValueRight = 0;
	encoderValueLeft = 0;
}