#pragma once
// #include <iostream>
#include <cmath>
// #include<fstream>

struct vertex {
  int x,y;
};

struct graph {
  int dist;
  struct vertex v[4];
  struct vertex prev;
};

// extern struct graph;

// void print_maze();

void init_adjacency();

void assign_dist();

void maze_wallinput(int x,int y,int i);

struct vertex maze_update(int x,int y,int z);