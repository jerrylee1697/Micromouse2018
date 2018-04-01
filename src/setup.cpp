#include "../inc/setup.h"
#include "../inc/macros.h"
#include "../inc/encoders.h"
#include <Arduino.h>

void ledSetup() {
	pinMode(TeensyLED, OUTPUT);
}

void motorsSetup() {
	pinMode(M1Forward, OUTPUT);	// Left Motor Logic
	pinMode(M1Reverse, OUTPUT);
	pinMode(M2Forward, OUTPUT);	// Right Motor Logic
	pinMode(M2Reverse, OUTPUT);
}

void encodersSetup() {
	pinMode(EncoderL_A, INPUT);
	pinMode(EncoderL_B, INPUT);
	pinMode(EncoderR_A, INPUT);
	pinMode(EncoderR_B, INPUT);
}

void receiversSetup() {
	pinMode(Receiver_L, INPUT);
	pinMode(Receiver_R, INPUT);
	pinMode(Receiver_FL, INPUT);
	pinMode(Receiver_FR, INPUT);
}

void emittersSetup() {
	pinMode(Emitter_L, OUTPUT);
	pinMode(Emitter_R, OUTPUT);
	pinMode(Emitter_FL, OUTPUT);
	pinMode(Emitter_FR, OUTPUT);
}

void initializePinModes() {
  motorsSetup();
  encodersSetup();
  receiversSetup();
  emittersSetup();
  ledSetup();
}

void attachInterrupts() {
  attachInterrupt(EncoderL_A, countLeftEncoderA, CHANGE);
  attachInterrupt(EncoderL_B, countLeftEncoderB, CHANGE);
  attachInterrupt(EncoderR_A, countRightEncoderA, CHANGE);
  attachInterrupt(EncoderR_B, countRightEncoderB, CHANGE);
}

