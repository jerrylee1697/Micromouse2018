#include "../inc/motors.h"
#include "../inc/macros.h"
#include "../inc/pid.h"
#include "../inc/pwm.h"
#include <Arduino.h>

volatile int MotorRightForward = 50;
volatile int MotorRightReverse = 0;
volatile int MotorLeftForward = 50;
volatile int MotorLeftReverse = 0;

void Forward() {
	PID();
	analogWrite(M1Forward, MotorLeftForward);
	analogWrite(M1Reverse, MotorLeftReverse);
	analogWrite(M2Forward, MotorRightForward);
	analogWrite(M2Reverse, MotorRightReverse);
}

void RightTurn() {
	// analogWrite(M1Forward, 0);
	// analogWrite(M1Reverse, 0);
	// analogWrite(M2Forward, 0);
	// analogWrite(M2Reverse, 0);
	// delay(2500);
	while (encoderValueLeft - encoderValueRight == 50)
	analogWrite(M1Forward, 30);
	analogWrite(M1Reverse, 0);
	analogWrite(M2Forward, 0);
	analogWrite(M2Reverse, 30);
	// delay(250);

	MotorRightForward = 0;
	MotorRightReverse = 0;
	MotorLeftForward = 0;
	MotorLeftReverse = 0;
	// delay(2500);
	// ResetEncoders();
	MotorRightForward = 50;
	MotorRightReverse = 0;
	MotorLeftForward = 50;
	MotorLeftReverse = 0;
}