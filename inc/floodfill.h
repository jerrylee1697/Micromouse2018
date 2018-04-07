#pragma once

#define NORTH	1
#define EAST	2
#define SOUTH	4
#define WEST	8

class Vertex {
	public:
		vector<Vertex*> adjacent;
		vector<bool> walls = {false,false,false,false}; // N(0), E(1), S(2), W(3)
		int distance;
		bool visited; //has it been traversed yet?
		int numWalls;
		int position;
};

class Graph : public Vertex {
	private:
		vector<Vertex> vertices;
		int mazeSize;
		vector<Vertex*> stack;
	public:
		Graph(int);
		void addEdge(Vertex*, int);
		bool checkEdge(Vertex* currCell, int wall); //does it exist?
		void updateDist();
		void printGraph(Vertex*);
		void populate(); //populate initial maze with distances
		void initialize(); //add maze borders and adjacent vertices
		void floodfill(int);
		void addWalls(vector<int> rows);
};