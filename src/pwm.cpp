#include "../inc/pwm.h"
#include "../inc/macros.h"
#include "../inc/encoders.h"
#include <Arduino.h>

int leftBaseSpeed = 0;
int rightBaseSpeed = 0;
// volatile bool startingCell = false;

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
