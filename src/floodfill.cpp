//for this version DON'T use the test maze. The wall values are hard coded 
//using maze_wallinput so just run the whole thing.

// #include <iostream>
#include <cmath>
// #include<fstream>
#include "../inc/floodfill.h"
//using namespace std;



struct graph m[16][16];

// void print_maze() {
//     int i,j;
         
//     for(i=0;i<16;i++) {
//        for(j=0;j<16;j++) {
//           //printf("%3d",m[j][i].dist); 
//           printf("(%d,%d)",m[j][i].v[0].x,m[j][i].v[0].y);                        
//        }
//      printf("\n\n");
//      }
// }

void init_adjacency() {
  int i,j;
    for(i = 0;i < 16; i++) {
      for(j=0;j<16;j++) {
                      
                      m[i][j].v[0].x = i; m[i][j].v[0].y = j-1;
                      m[i][j].v[3].x = i; m[i][j].v[3].y = j+1;
                      m[i][j].v[2].x = i+1; m[i][j].v[2].y = j;
                      m[i][j].v[1].x = i-1; m[i][j].v[1].y = j;
      }
  }
     
}

void assign_dist() {
  int i,j;
    for(i = 0;i < 16; i++) {
      for(j = 0;j < 16;j++) {
        if((i < 8)&&(j < 8)) {m[i][j].dist = 14-j-i;}
            if((i>=8)&&(j<8)) {m[i][j].dist = m[15-i][j].dist;}
            if((i<8)&&(j>=8)) {m[i][j].dist = m[i][15-j].dist;}
            if((i>=8)&&(j>=8)) {m[i][j].dist = m[15-i][15-j].dist;}
      }
    }

}

void maze_wallinput(int x,int y,int i) {
  if(m[x][y].v[i].x!=-1&&m[x][y].v[i].x!=16&&m[x][y].v[i].y!=-1&&m[x][y].v[i].y!=16)
  {
  m[(m[x][y].v[i].x)][(m[x][y].v[i].y)].v[3-i].x=-1;m[(m[x][y].v[i].x)][(m[x][y].v[i].y)].v[3-i].y=-1;
  }


  m[x][y].v[i].x=-1;m[x][y].v[i].y=-1;
}    

struct vertex maze_update(int x,int y,int z) {
  int i,j,h=400;
  int x1,y1;

  for(i=0;i<4;i++){
    x1 = m[x][y].v[i].x;
    y1 = m[x][y].v[i].y;
    if(x1 != -1 && x1!= 16 && y1!= -1 && y1 != 16) {

      if(m[(x1)][(y1)].dist == (m[x][y].dist) - 1 ) { break;}
      
      if(m[(x1)][(y1)].dist <= h) {
        h = m[(x1)][(y1)].dist;
        j = i;
      }
    }
  }
   
  if(i==4) {
    m[x][y].dist = (m[m[x][y].v[j].x][m[x][y].v[j].y].dist)+1;     

    for(i=0;i<4;i++) {
      if(m[x][y].prev.x!=0 || m[x][y].prev.y!=15) {
        maze_update(m[x][y].prev.x,m[x][y].prev.y,1);
      }
    }
  }
   
  for(i=0;i<4;i++) {
    int x1 = m[x][y].v[i].x;
    int y1 = m[x][y].v[i].y;
    if(x1 != -1 && x1 != 16 && y1 != -1 && y1 != 16){ 
      if(m[(x1)][(y1)].dist ==(m[x][y].dist)-1  ) {break;}
    }
  }
  
  if(i != 4) {
    if((m[x][y].prev.x!=0 || m[x][y].prev.y!=15)&& z==0 ) {
      m[(x1)][(y1)].prev.x=x; m[(x1)][(y1)].prev.y=y;
    }
    return m[x][y].v[i];
  }
   
return m[x][y].v[i];   
}    

/*
int main() {
  struct vertex c;

  init_adjacency();
  assign_dist();
  print_maze();

  maze_wallinput(0,14,2);
  maze_wallinput(7,8,1);
  maze_wallinput(0,13,0);
  maze_wallinput(0,13,2);
  maze_wallinput(1,14,0);
  
  c=maze_update(0,15,0);
    printf("\n(%d,%d)\n",c.x,c.y);   
    for(int i=0;m[c.x][c.y].dist!=0;i++)
    {
    c=maze_update(c.x,c.y,0);
    printf("\n(%d,%d)\n",c.x,c.y);
    }
  return 0;
} */