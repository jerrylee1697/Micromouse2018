#include "../inc/state.h"
#include "../inc/sensors.h"
#include "../inc/movement.h"
#include <Arduino.h>

int nextCellState = LEFT + RIGHT;
int stateCount = 0;

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
		stateCount = 0;
		if (random(millis()) % 3 == 2) {
			turnRight();
		}
		else if (random(millis()) % 3 == 1) {
			turnLeft();
		}
		moveOneCell();
		break;
	case FRONT:
		stateCount = 0;
		if (random(millis()) % 2) {   // Turn left or right randomly
			turnLeft();
		}
		else {
			turnRight();
		}
		moveOneCell();
		break;
	case RIGHT:
		stateCount = 0;
		if (random(millis()) % 2) {   // Turn left or go forward randomly
			turnLeft();
		}
		moveOneCell();
		break;
	case LEFT:
		stateCount = 0;
		if (random(millis()) % 2) {   // Turn right or go forward randomly
			turnRight();
		}
			moveOneCell();
		break;
	case FRONT + RIGHT:
		stateCount = 0;
		turnLeft();
		moveOneCell();
		break;
	case FRONT + LEFT:
		stateCount = 0;
		turnRight();
		moveOneCell();
		break;
	case RIGHT + LEFT:
		stateCount += 1;
		if (stateCount++ >= 16) {
			turnAround();
			stateCount = 0;
		}
		moveOneCell();
		break;
	case FRONT + RIGHT + LEFT:
		stateCount = 0;
		turnAround();
		moveOneCell();
		break;
	default:
		Serial.println("Error: Default");
		break;
	}
}

void solveRightHand() {
  switch (nextCellState) {
    case 0:
    	turnRight();
      moveOneCell();
      break;
    case FRONT:
        turnRight();
        moveOneCell();
      break;
    case RIGHT:
        moveOneCell();
      break;
    case LEFT:
       turnRight();
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

void floodfill() {
	// i = 0 1 2 3
	// Up, Left, Right, Down

	// Maze orientation
	//--------------
	//(0,0)		(0,15)
	//
	//(15,0)	(15,15)
	//--------------


	struct vertex c;
	
	init_adjacency();
	assign_dist();

	//    Format: (x, y)
	pair(int, int) start (0, 0);
	pair(int, int) goal (7, 7);
	pair(int, int) current(0, 0);
	pair cellCheck;

	stack <pair<int,int> > stack;

	stack.push(start);
	while (start != goal) {
		while (!stack.empty()) {
			cellCheck = stack.pop();
			if ()
		}

	}






	return 0;
}