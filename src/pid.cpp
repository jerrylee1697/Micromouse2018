#include "../inc/pid.h"
#include "../inc/encoders.h"
#include "../inc/motors.h"

int error = 0;

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