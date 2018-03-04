#include "../inc/led.h"
#include "../inc/macros.h"
#include <Arduino.h>

bool ledFlag = false;

void blinkLED() {
	digitalWrite(TeensyLED, !ledFlag);
	ledFlag = !ledFlag;
}
