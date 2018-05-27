// #include <iostream>
// #include <cmath>

#ifndef FLOODFILL_H
#define FLOODFILL_H

#define STACK_MAX 100
const int SIZ = 16;

struct vertex {
  int x,y;
};

struct Stack {
    vertex     data[STACK_MAX];
    int     size;
};
typedef struct Stack Stack;

struct graph {
	int dist;
	struct vertex v[4];
  struct vertex prev;
  int x,y;
  bool visited;
};

extern struct graph m[SIZ][SIZ];
extern struct Stack stack;
extern Stack* s;

// void print_maze();

void Stack_Init(Stack *);

void init_adjacency();

void assign_dist();

struct vertex floodfill(int x,int y);

void updateDist();

void maze_wallinput(int x, int y, int i);

// struct vertex maze_update(int x,int y,int z);

#endif