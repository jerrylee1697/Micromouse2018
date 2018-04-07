#include "../inc/sensors.h"
#include "../inc/macros.h"
#include "../inc/delay.h"
#include "../inc/state.h"
#include <Arduino.h>

int ambientValueLeft;
int ambientValueFrontLeft;
int ambientValueFrontRight;
int ambientValueRight;

int Receiver_L_Reading;
int Receiver_FL_Reading;
int Receiver_FR_Reading;
int Receiver_R_Reading;

int Receiver_L_Reading_Raw;
int Receiver_FL_Reading_Raw;
int Receiver_FR_Reading_Raw;
int Receiver_R_Reading_Raw;

int sensorError;

bool frontWall;
bool leftWall;
bool rightWall;

int thresholdFront = 50;
int thresholdSide = 50;		// Threshold for Wall on side
int thresholdUpperFront = 150; // Threshold for when mouse close to front wall detecting side walls

int targetLeft = 0;//140;
int targetRight = 0;//190;
int targetFront = 290;	// 60 - Threshold for Wall in front from Cell Boundary
int targetFront2 = 260;	// 30 - Threshold for Wall in front from Half Cell further than boundary

void readSensors() {
	// Emitter Duty Cycle = 0.025 for mosfets

	// ---- LEFT EMITTER ---- //
	ambientValueLeft = analogRead(Receiver_L);
	digitalWrite(Emitter_L, HIGH);
	delayMicroseconds(40); // Charge time for receiver, Specific time found through using an oscilloscope
	Receiver_L_Reading_Raw = analogRead(Receiver_L);
	Receiver_L_Reading = Receiver_L_Reading_Raw - ambientValueLeft;
	digitalWrite(Emitter_L, LOW);

	// ---- RIGHT EMITTER ---- //
	delayMicroseconds(25); // Delay to allow receiver to fully discharge before taking ambient reading
	ambientValueRight = analogRead(Receiver_R);
	digitalWrite(Emitter_R, HIGH);
	delayMicroseconds(40);
	Receiver_R_Reading_Raw = analogRead(Receiver_R);
	Receiver_R_Reading = Receiver_R_Reading_Raw - ambientValueRight;
	digitalWrite(Emitter_R, LOW);

	// ---- FRONT LEFT EMITTER ---- //
	delayMicroseconds(25); // Delay to allow receiver to fully discharge before taking ambient reading
	ambientValueFrontLeft = analogRead(Receiver_FL);
	digitalWrite(Emitter_FL, HIGH);
	delayMicroseconds(40); // Delay to allow receiver to fully charge
	Receiver_FL_Reading_Raw = analogRead(Receiver_FL);
	Receiver_FL_Reading = Receiver_FL_Reading_Raw - ambientValueFrontLeft;
	digitalWrite(Emitter_FL, LOW);

	// ---- FRONT RIGHT EMITTER ---- //
	delayMicroseconds(25); // Delay to allow receiver to fully discharge before taking ambient reading
	ambientValueFrontRight = analogRead(Receiver_FR);
	digitalWrite(Emitter_FR, HIGH);
	delayMicroseconds(40); 
	Receiver_FR_Reading_Raw = analogRead(Receiver_FR);
	Receiver_FR_Reading = Receiver_FR_Reading_Raw - ambientValueFrontRight;
	digitalWrite(Emitter_FR, LOW);

	detectWalls();
	getSensorError();
	// printSensors();
}

void getSensorError() {

	// if (Receiver_R_Reading < thresholdUpperFront || Receiver_L_Reading < thresholdUpperFront) {
	// 	if (leftWall == true && rightWall == true) {
	// 		sensorError = Receiver_FR_Reading - Receiver_FL_Reading;
	// 	}
	// 	else if (leftWall == true && rightWall == false) {
	// 		sensorError = targetLeft - Receiver_FL_Reading;
	// 	}
	// 	else if (rightWall == true && leftWall == false) {
	// 		sensorError = Receiver_FR_Reading - targetRight;
	// 	}
	// 	else if (rightWall == false && leftWall == false) {
	// 		sensorError = 0;
	// 	}
	// }
	// else {
	// 	sensorError = Receiver_L_Reading - Receiver_R_Reading;
	// 	sensorError *= 3;
	// }

	if (Receiver_R_Reading < thresholdUpperFront || Receiver_L_Reading < thresholdUpperFront) {
		if (leftWall == true && rightWall == true) {
			sensorError = Receiver_FR_Reading - Receiver_FL_Reading - (targetRight - targetLeft);
		}
		else if (leftWall == true && rightWall == false) {
			sensorError = targetLeft - Receiver_FL_Reading;
		}
		else if (rightWall == true && leftWall == false) {
			sensorError = Receiver_FR_Reading - targetRight;
		}
		else if (rightWall == false && leftWall == false) {
			sensorError = 0;
		}
		}
		else {
			sensorError = 0;
		}

		// if (nextCellState == FRONT) {
		// 	if (frontWall)
		// 		sensorError = (Receiver_L_Reading - Receiver_R_Reading) * 2;
		// }

	// if (frontWall) {
	// 	sensorError = (Receiver_L_Reading - Receiver_R_Reading) * 3;
	// }

	if (Receiver_R_Reading > thresholdUpperFront || Receiver_L_Reading > thresholdUpperFront) {
		sensorError = (Receiver_L_Reading - Receiver_R_Reading) ;
	}
}

void printSensorsRaw() {
	Serial.print("Left Raw: ");
	Serial.println(Receiver_L_Reading_Raw);
	Serial.print("Front Left Raw: ");
	Serial.println(Receiver_FL_Reading_Raw);
	Serial.print("Front Right Raw: ");
	Serial.println(Receiver_FR_Reading_Raw);
	Serial.print("Right Raw: ");
	Serial.println(Receiver_R_Reading_Raw);
	Serial.print("\n");
}

void printSensorsAmbient() {
	Serial.print("Left Ambient: ");
	Serial.println(ambientValueLeft);
	Serial.print("Front Left Ambient: ");
	Serial.println(ambientValueFrontLeft);
	Serial.print("Front Right Ambient: ");
	Serial.println(ambientValueFrontRight);
	Serial.print("Right Ambient: ");
	Serial.println(ambientValueRight);
	Serial.print("\n");
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

void detectWalls() {
	if (Receiver_R_Reading > thresholdFront || Receiver_L_Reading > thresholdFront) {
		frontWall = true;
	}
	else {
		frontWall = false;
	}

	if (Receiver_FL_Reading > thresholdSide) {
		leftWall = true;
	}
	else {
		leftWall = false;
	}
	
	if (Receiver_FR_Reading > thresholdSide) {
		rightWall = true;
	}
	else {
		rightWall = false;
	}
}