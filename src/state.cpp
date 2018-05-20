#include "../inc/state.h"
#include "../inc/sensors.h"
#include "../inc/movement.h"
#include "../inc/floodfill.h"
#include <Arduino.h>


int nextCellState = LEFT + RIGHT;
int stateCount = 0;
int orientation = 0; // Default Orientation : Front facing Right Side
					 // In graph, Facing bottom

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

// void floodfill() {
// 	Graph maze(16);
// 	maze.populate();
//   	maze.initialize();
//   	Vertex currCell = &(this->vertices.at(0));
//   	Vertex prev;

//   	while () {
// 		if ((orientation % 4) < 0) {
// 			orientation = (orientation % 4) + 4;
// 		}
// 		else {
// 			orientation = orientation % 4;
// 		}
// 		switch(nextCellState) {
// 			case FRONT:
// 				add_edge(currCell, (orientation + 0) % 4);
// 				break;
// 			case RIGHT:
// 				add_edge(currCell, (orientation + 1) % 4);
// 				break;
// 			case LEFT:
// 				add_edge(currCell, (orientation + 3) % 4);
// 				break;
// 			case FRONT + RIGHT:
// 				// Front
// 				add_edge(currCell, (orientation + 0) % 4);
// 				// Right
// 				add_edge(currCell, (orientation + 1) % 4);
// 				break;
// 			case FRONT + LEFT:
// 				// Front
// 				add_edge(currCell, (orientation + 0) % 4);
// 				// Left
// 				add_edge(currCell, (orientation + 3)% 4);
// 				break;
// 			case RIGHT + LEFT:
// 				// Right
// 				add_edge(currCell, (orientation + 1) % 4);
// 				// Lef
// 				add_edge(currCell, (orientation + 3) % 4);
// 				break;
// 			case FRONT + RIGHT + LEFT:
// 				// Front
// 				add_edge(currCell, (orientation + 0) % 4);
// 				// Right
// 				add_edge(currCell, (orientation + 1) % 4);
// 				// Left
// 				add_edge(currCell, (orientation + 3) % 4);
// 				break;
// 			default:
// 				Serial.println("Error: Default");
// 				break;
// 		}

// 		prev = currCell;
// 		currCell = floodfill(currCell);
// 		change = currCell.position - prev.position;

// 		if (change == -1) {
// 			while ((orientation % 4) != 3) {
// 				if ((orientation % 4) < 0) {
// 					orientation = (orientation % 4) + 4;
// 				}
// 				else {
// 					orientation = orientation % 4;
// 				}
// 					turnLeft();
// 			}
// 		}
// 		else if (change == 1) {
// 			while ((orientation % 4) != 1) {
// 				if ((orientation % 4) < 0) {
// 					orientation = (orientation % 4) + 4;
// 				}
// 				else {
// 					orientation = orientation % 4;
// 				}
// 				turnLeft();
// 			}
// 		}
// 		else if (change == -16) {
// 			while ((orientation % 4)!= 2) {
// 				if ((orientation % 4) < 0) {
// 					orientation = (orientation % 4) + 4;
// 				}
// 				else {
// 					orientation = orientation % 4;
// 				}
// 				turnLeft();
// 			}
// 		}
// 		else if (change == 16) {
// 			while ((orientation % 4) != 0) {
// 				if ((orientation % 4) < 0) {
// 					orientation = (orientation % 4) + 4;
// 				}
// 				else {
// 					orientation = orientation % 4;
// 				}
// 				turnLeft();
// 			}
// 		}
// 		moveOneCell();

// 	// i = 0 1 2 3
// 	// Up, Right, Down, Left

// 	// Maze orientation
// 	//--------------
// 	//(0,0)		(0,15)
// 	//
// 	//(15,0)	(15,15)
// 	//--------------


// 	struct vertex c;
	
// 	init_adjacency();
// 	assign_dist();

// 	//    Format: (x, y)
// 	// pair<int, int> start (0, 0);
// 	// pair(int, int) goal (7, 7);
// 	// pair(int, int) current(0, 0);
// 	int start_x = 0;
// 	int start_y = 15;
// 	int goal_x = 7;
// 	int goal_y = 7;
// 	int current_x = start_x;
// 	int current_y = start_y;
	
// 	// Hardcode first cell
// 	// Left
// 	maze_wallinput(current_x, current_y, (orientation + 3) % 4);
// 	// Right
// 	maze_wallinput(current_x, current_y, (orientation + 1) % 4);
// 	c = maze_update(current_x, current_y, 0);
// 	current_x = c.x;
// 	current_y = c.y;

// 	moveOneCell();

// 	while (current_x != goal_x && current_y != goal_y) {
// 		if ((orientation % 4) < 0) {
// 			orientation = (orientation % 4) + 4;
// 		}
// 		else {
// 			orientation = orientation % 4;
// 		}
// 		switch(nextCellState) {
// 			case FRONT:
// 				maze_wallinput(current_x, current_y, (orientation + 0) % 4);
// 				break;
// 			case RIGHT:
// 				maze_wallinput(current_x, current_y, (orientation + 1) % 4);
// 				break;
// 			case LEFT:
// 				maze_wallinput(current_x, current_y, (orientation + 3) % 4);
// 				break;
// 			case FRONT + RIGHT:
// 				// Front
// 				maze_wallinput(current_x, current_y, (orientation + 0) % 4);
// 				// Right
// 				maze_wallinput(current_x, current_y, (orientation + 1) % 4);
// 				break;
// 			case FRONT + LEFT:
// 				// Front
// 				maze_wallinput(current_x, current_y, (orientation + 0) % 4);
// 				// Left
// 				maze_wallinput(current_x, current_y, (orientation + 3)% 4);
// 				break;
// 			case RIGHT + LEFT:
// 				// Right
// 				maze_wallinput(current_x, current_y, (orientation + 1) % 4);
// 				// Left
// 				maze_wallinput(current_x, current_y, (orientation + 3) % 4);
// 				break;
// 			case FRONT + RIGHT + LEFT:
// 				// Front
// 				maze_wallinput(current_x, current_y, (orientation + 0) % 4);
// 				// Right
// 				maze_wallinput(current_x, current_y, (orientation + 1) % 4);
// 				// Left
// 				maze_wallinput(current_x, current_y, (orientation + 3) % 4);
// 				break;
// 			default:
// 				Serial.println("Error: Default");
// 				break;
// 		}

// 		// maze_update returns vertex c
// 		// Vertex c = next cell to traverse to
// 		c = maze_update(current_x, current_y, 0);

// 		int change_x = current_x - c.x;
// 		int change_y = current_y - c.y;

// 		// Check orientation to make mouse point in correct direction
// 		if (change_x == -1) {
// 			while ((orientation % 4) != 3) {
// 				if ((orientation % 4) < 0) {
// 					orientation = (orientation % 4) + 4;
// 				}
// 				else {
// 					orientation = orientation % 4;
// 				}
// 					turnLeft();
// 			}
// 		}
// 		else if (change_x == 1) {
// 			while ((orientation % 4) != 1) {
// 				if ((orientation % 4) < 0) {
// 					orientation = (orientation % 4) + 4;
// 				}
// 				else {
// 					orientation = orientation % 4;
// 				}
// 				turnLeft();
// 			}
// 		}
// 		else if (change_y == -1) {
// 			while ((orientation % 4)!= 2) {
// 				if ((orientation % 4) < 0) {
// 					orientation = (orientation % 4) + 4;
// 				}
// 				else {
// 					orientation = orientation % 4;
// 				}
// 				turnLeft();
// 			}
// 		}
// 		else if (change_y == 1) {
// 			while ((orientation % 4) != 0) {
// 				if ((orientation % 4) < 0) {
// 					orientation = (orientation % 4) + 4;
// 				}
// 				else {
// 					orientation = orientation % 4;
// 				}
// 				turnLeft();
// 			}
// 		}
// 		moveOneCell();

// 		current_x = c.x;
// 		current_y = c.y;
// 	}

// 	return;
// }

