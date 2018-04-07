#include <iostream>
#include <vector>
#include <cmath>
#include<fstream>
using namespace std;

Graph::Graph(int size) {
    mazeSize = size;
    vertices.resize(size * size);

}

void Graph::initialize() {
	//set up borders around maze
	for(int i = 0; i < mazeSize * mazeSize; ++i) {
		this->vertices.at(i).position = i; //initialize position # in array
		this->vertices.at(i).walls.resize(4);
		this->vertices.at(i).numWalls = 0;
		if((i - mazeSize) < 0) { //upper maze border
			this->vertices.at(i).walls.at(0) = true;
		}
		if((i + mazeSize) >= (mazeSize * mazeSize)) { //lower maze border
			this->vertices.at(i).walls.at(2) = true;
		}
		if((i % mazeSize) == 0) { //left maze border
			this->vertices.at(i).walls.at(3) = true;
		}
		if((i + 1) % mazeSize == 0) { //right border
			this->vertices.at(i).walls.at(1) = true;
		}
	}
	//add lists of adjacent vertices
	for(int i = 0; i < mazeSize * mazeSize; ++i) {
		if(this->vertices.at(i).walls.at(0) == false) { //check upper
			this->vertices.at(i).adjacent.push_back(&(this->vertices.at(i - mazeSize)));
		}
		if(this->vertices.at(i).walls.at(2) == false) { //check lower
			this->vertices.at(i).adjacent.push_back(&(this->vertices.at(i + mazeSize)));
		}
		if(this->vertices.at(i).walls.at(3) == false) { //check left
			this->vertices.at(i).adjacent.push_back(&(this->vertices.at(i - 1)));
		}
		if(this->vertices.at(i).walls.at(1) == false) { //check right
			this->vertices.at(i).adjacent.push_back(&(this->vertices.at(i + 1)));
		}
	}
}

void Graph::populate() {
	//add in initial distances
	int num = mazeSize - 2;
	int i = 0;
	while(i < mazeSize * mazeSize) {
		for(int a = num; a >= num / 2; --a) {
			for(int j = a; j >= a - num / 2; --j) {
				this->vertices.at(i).distance = j;
				++i;
			}
			for(int j = a - num/ 2; j <= a; ++j) {
				this->vertices.at(i).distance = j;
				++i;
			} cout << endl;
			
		}
		num = mazeSize - 2;
		for (int a = num / 2; a <= num; ++a) {
			
			for(int j = a; j >= a - num / 2; --j) {
				this->vertices.at(i).distance = j;
				++i;
			} 
			for(int j = a - num / 2; j <= a; ++j) {
				this->vertices.at(i).distance = j;
				++i;
			}cout << endl;
			
		}
	} cout << endl;
}

void Graph::updateDist() {
	int i = 0;
	Vertex* top = this->stack.back();
	Vertex* minimum = this->stack.back();

	for(i = 0; i < top->adjacent.size(); ++i) {
		if(top->adjacent.at(i)->distance < minimum->distance) {
			minimum = top->adjacent.at(i);
		}
	} 
	//for(i = 0; i < top->adjacent.size(); ++i) {cout << top->adjacent.at(i)->position << " ";}
		if(top->distance != minimum->distance + 1 && top->distance != 0) { //are the distances correct?
			top->distance = minimum->distance + 1;
			this->stack.pop_back();
			for(i = 0; i < top->adjacent.size(); ++i) {
				this->stack.push_back(top->adjacent.at(i));
			}
		} else {this->stack.pop_back();}


}
void Graph::floodfill(int start) {
	Vertex* currCell = &(this->vertices.at(start));
	currCell->visited = true;
	Vertex* closest = currCell;
	Vertex* toErase;
	
	while(currCell->distance != 0) {
		this->stack.clear();

		//go through adjacnecy list of current cell to find non-visted cell with smallest distance
		for(int i = 0; i < currCell->adjacent.size(); ++i) {
			if(currCell->adjacent.at(i)->distance < closest->distance && !currCell->adjacent.at(i)->visited) {
				closest = currCell->adjacent.at(i);
			}
		} 
		//if there are no unvisited cells, choose the one with the smallest distance
		if(closest == currCell) {
			for(int i = 0; i < currCell->adjacent.size(); ++i) {
			if(currCell->adjacent.at(i)->distance < closest->distance) {
				closest = currCell->adjacent.at(i);
			}
			}
		}
		
		currCell = closest;
		currCell->visited = true;

		//begin checking for new walls
		int i = 0;
		int k = 0;
		//North
		if(currCell->walls.at(0) == true && (currCell->position - mazeSize) > 0) { //North
			this->stack.push_back(currCell);
			this->stack.push_back(currCell-mazeSize);
			for(i = 0; i < currCell->adjacent.size(); ++i) {
				if(currCell->adjacent.at(i) == currCell - mazeSize) {
					toErase = currCell->adjacent.at(i);
				for(k = 0; k < toErase->adjacent.size(); ++k) {
					if(toErase->adjacent.at(k) == currCell) {
						break;
					}
				}
				toErase->adjacent.erase(toErase->adjacent.begin()+k);
				currCell->adjacent.erase(currCell->adjacent.begin() + i);
				}
			} 
		} 
		//East
		if(currCell->walls.at(1) == true && ((currCell->position + 1) % mazeSize) != 0) { //East
			this->stack.push_back(currCell); //push current cell to stack
			this->stack.push_back(currCell + 1); //push eastern cell to stack
			for(i = 0; i < currCell->adjacent.size(); ++i) {
				//erase cells from eachother's adjaceny lists
				if(currCell->adjacent.at(i) == currCell + 1) {
					toErase = currCell->adjacent.at(i);
					for(k = 0; k < toErase->adjacent.size(); ++k) {
						if(toErase->adjacent.at(k) == currCell) {
							break;
						}
					}
					toErase->adjacent.erase(toErase->adjacent.begin()+k);
					currCell->adjacent.erase(currCell->adjacent.begin() + i);
					
				}
			}
			
		}
		//South
		if(currCell->walls.at(2) == true && (currCell->position + mazeSize) < mazeSize*mazeSize) { //South
			this->stack.push_back(currCell); //push current cell to stack
			this->stack.push_back(currCell + mazeSize); //push southern cell to stack
			for(i = 0; i < currCell->adjacent.size(); ++i) {
				if(currCell->adjacent.at(i) == currCell + mazeSize) { //find the southern cell in adjacency list and mark it for erasing
					toErase = currCell->adjacent.at(i);
					for(k = 0; k < toErase->adjacent.size(); ++k) {
						if(toErase->adjacent.at(k) == currCell) {
							break;
						}
					}
					toErase->adjacent.erase(toErase->adjacent.begin()+k);
					currCell->adjacent.erase(currCell->adjacent.begin() + i);
				}
			} 
		}
		//West
		if(currCell->walls.at(3) == true && (currCell->position % mazeSize) != 0) { //West
			this->stack.push_back(currCell);
			this->stack.push_back(currCell - 1);
			for(i = 0; i < currCell->adjacent.size(); ++i) {
				if(currCell->adjacent.at(i) == currCell - 1) {
					toErase = currCell->adjacent.at(i);
				for(k = 0; k < toErase->adjacent.size(); ++k) {
					if(toErase->adjacent.at(k) == currCell) {
						break;
					}
				}
				toErase->adjacent.erase(toErase->adjacent.begin()+k);
				currCell->adjacent.erase(currCell->adjacent.begin() + i);
				}
			} 
		}
		
		while(this->stack.size() != 0) {
			this->updateDist();
		}
	}
}
void Graph::addEdge(Vertex* currCell, int wall) {
	if(currCell != 0) {
		currCell->walls.at(wall) = true;
	}
}

bool Graph::checkEdge(Vertex* currCell, int wall){
	if(currCell != 0){
		if(currCell->walls.at(wall) == 1){
			return true;
		}
		return false;
	}
	return false;
}

int main(int argc, char* argv[]) {
	Graph maze(size);

	maze.populate();
	maze.initialize();

	maze.floodfill(start);

	return 0;
}
