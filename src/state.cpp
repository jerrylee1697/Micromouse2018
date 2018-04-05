#include "../inc/state.h"
#include "../inc/sensors.h"
#include "../inc/movement.h"
#include <Arduino.h>

int nextCellState = LEFT + RIGHT;

void updateState() {
  nextCellState = 0;
  if (frontWall) {
    nextCellState += FRONT;
  }
  if (rightWall) {
    nextCellState += RIGHT;
  }
  if (leftWall) {
    nextCellState += LEFT;
  }
}


void navigate() {
	switch (nextCellState) {
	case 0:       // Randomly choose left, right, or straight
		if (random(millis()) % 3 == 2) {
			turnRight();
		}
		else if (random(millis()) % 3 == 1) {
			turnLeft();
		}
		moveOneCell();
		break;
	case FRONT:
		if (random(millis()) % 2) {   // Turn left or right randomly
			turnLeft();
		}
		else {
			turnRight();
		}
		moveOneCell();
		break;
	case RIGHT:
		if (random(millis()) % 2) {   // Turn left or go forward randomly
			turnLeft();
		}
		moveOneCell();
		break;
	case LEFT:
		if (random(millis()) % 2) {   // Turn right or go forward randomly
			turnRight();
		}
			moveOneCell();
		break;
	case FRONT + RIGHT:
		turnLeft();
		moveOneCell();
		break;
	case FRONT + LEFT:
		turnRight();
		moveOneCell();
		break;
	case RIGHT + LEFT:
		moveOneCell();
		break;
	case FRONT + RIGHT + LEFT:
		turnAround();
		moveOneCell();
		break;
	default:
		Serial.println("Error: Default");
		break;
	}
}