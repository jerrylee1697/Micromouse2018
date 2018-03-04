#include "../inc/sensors.h"
#include "../inc/macros.h"
#include "../inc/delay.h"
#include <Arduino.h>

int ambientValue;

int Receiver_L_Reading;
int Receiver_FL_Reading;
int Receiver_FR_Reading;
int Receiver_R_Reading;

void readSensors() {
	// Emitter Duty Cycle = 0.025 for mosfets

	// ---- LEFT EMITTER ---- //
	ambientValue = analogRead(Receiver_L);
	digitalWrite(Emitter_L, HIGH);
	delayMicroseconds(125);               // Emitter Duty Cycle = 0.025 of 1 so 0.025 of 5millis(5000micro) is 125
	Receiver_L_Reading = analogRead(Receiver_L) - ambientValue;
	digitalWrite(Emitter_L, LOW);

	// ---- FRONT LEFT EMITTER ---- //
	ambientValue = analogRead(Receiver_FL);
	digitalWrite(Emitter_FL, HIGH);
	delayMicroseconds(125);
	Receiver_FL_Reading = analogRead(Receiver_FL) - ambientValue;
	digitalWrite(Emitter_FL, LOW);

	// ---- FRONT RIGHT EMITTER ---- //
	ambientValue = analogRead(Receiver_FR);
	digitalWrite(Emitter_FR, HIGH);
	delayMicroseconds(125);
	Receiver_FR_Reading = analogRead(Receiver_FR);
	digitalWrite(Emitter_FR, LOW);

	// ---- RIGHT EMITTER ---- //
	ambientValue = analogRead(Receiver_R);
	digitalWrite(Emitter_R, HIGH);
	Receiver_R_Reading = analogRead(Receiver_R) - ambientValue;
	digitalWrite(Emitter_R, LOW);
}

void printSensors() {
	Serial.print("Left: ");
	Serial.println(Receiver_L_Reading);
	Serial.print("Front Left: ");
	Serial.println(Receiver_FL_Reading);
	Serial.print("Front Right: ");
	Serial.println(Receiver_FR_Reading);
	Serial.print("Right: ");
	Serial.println(Receiver_R_Reading);
	Serial.print("\n");
}