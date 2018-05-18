#include<stdio.h>
#include<stdlib.h>

struct cord{
       int x,y;
       };

struct grid{
       int value;
       
       struct cord d[4];   // order is up ,left ,right ,down.
       struct cord prev;
       };

struct grid m[16][16];

void print_maze()
{
     int i,j;
         
     for(i=0;i<16;i++)
     {
                      for(j=0;j<16;j++)
                      {
                      printf("%3d",m[j][i]);                         
                      }
     printf("\n\n");
     }
     }


  
void neighbours_assign()
{
     int i,j;
     for(i=0;i<16;i++)
     for(j=0;j<16;j++)
     {
                      
                      m[i][j].d[0].x=i;m[i][j].d[0].y=j-1;
                      m[i][j].d[3].x=i;m[i][j].d[3].y=j+1;
                      m[i][j].d[2].x=i+1;m[i][j].d[2].y=j;
                      m[i][j].d[1].x=i-1;m[i][j].d[1].y=j;
     }
     
}  

void maze_setup()
{
     int i,j;
     for(i=0;i<16;i++)
     for(j=0;j<16;j++)
     {
               if((i<8)&&(j<8))       m[i][j].value=14-j-i;
               if((i>=8)&&(j<8))      m[i][j].value=m[15-i][j].value;  
               if((i<8)&&(j>=8))      m[i][j].value=m[i][15-j].value;
               if((i>=8)&&(j>=8))     m[i][j].value=m[15-i][15-j].value;               
     
     }
}

struct cord maze_update(int x,int y,int z)
{
     int i,j,h=400;
     for(i=0;i<4;i++)
     {
                     if(m[x][y].d[i].x!=-1&&m[x][y].d[i].x!=16&&m[x][y].d[i].y!=-1&&m[x][y].d[i].y!=16)
                     {
                     if(m[(m[x][y].d[i].x)][(m[x][y].d[i].y)].value ==(m[x][y].value)-1 )
                     { break;}
                     //printf("\n***%d***\n",i);
                     
                     if(m[(m[x][y].d[i].x)][(m[x][y].d[i].y)].value<=h)
                     {
                     h=m[(m[x][y].d[i].x)][(m[x][y].d[i].y)].value;
                     j=i;
                     }
                     
                     
                     }
     }
     
     if(i==4)
     {
             
            m[x][y].value=(m[m[x][y].d[j].x][m[x][y].d[j].y].value)+1;     
      // printf("\n***%d***\n",m[0][15].d[0].x);
     
    
    
     //printf("\n****************\n");
     for(i=0;i<4;i++)
     {
             if(m[x][y].prev.x!=0 || m[x][y].prev.y!=15)
             {
                                  maze_update(m[x][y].prev.x,m[x][y].prev.y,1);//printf("\n*****(%d,%d)\n",x,y);
                                  
                                  }
             }
    // else return m[x][y].d[i];
     }
     
     
     
     for(i=0;i<4;i++)
     {
                     if(m[x][y].d[i].x!=-1&&m[x][y].d[i].x!=16&&m[x][y].d[i].y!=-1&&m[x][y].d[i].y!=16)
                     {
                     if(m[(m[x][y].d[i].x)][(m[x][y].d[i].y)].value ==(m[x][y].value)-1  )
                     { break;}
                     }
     }
    // j=i;
     if(i!=4)
     {
             if((m[x][y].prev.x!=0 || m[x][y].prev.y!=15)&& z==0 )
             {m[(m[x][y].d[i].x)][(m[x][y].d[i].y)].prev.x=x; m[(m[x][y].d[i].x)][(m[x][y].d[i].y)].prev.y=y;
            // printf("***%d %d %d****",x,y,i);}
            }
             return m[x][y].d[i];}
     /*printf("\n****************\n");
     for(i=0;i<4;i++)
     if(m[x][y].d[i].x!=-1&&m[x][y].d[i].x!=16&&m[x][y].d[i].y!=-1&&m[x][y].d[i].y!=16)
     {
     maze_update(m[x][y].d[i].x,m[x][y].d[i].y);printf("\n*****(%d,%d)\n",x,y);
     }
     */
     
           
}     
   
void maze_wallinput(int x,int y,int i)
{
     if(m[x][y].d[i].x!=-1&&m[x][y].d[i].x!=16&&m[x][y].d[i].y!=-1&&m[x][y].d[i].y!=16)
     {
     m[(m[x][y].d[i].x)][(m[x][y].d[i].y)].d[3-i].x=-1;m[(m[x][y].d[i].x)][(m[x][y].d[i].y)].d[3-i].y=-1;
     }
     
     
     m[x][y].d[i].x=-1;m[x][y].d[i].y=-1;
     }    
     
main()
{
      
   //   maze_clear();
      int i,j;
      struct cord c;
      maze_setup();
      
      neighbours_assign();
     
  //   *******************************
     // m[6][9].value=-1;m[6][7].value=-1;m[5][8].value=-1;m[7][8].value=-1;
      //maze_wallinput(0,14,1);
   maze_wallinput(0,14,2);
      //maze_wallinput(0,15,3);     
      
      maze_wallinput(7,8,1);
      maze_wallinput(0,13,0);
      maze_wallinput(0,13,2);
      maze_wallinput(1,14,0);     
     /* maze_update(0,13);
      maze_update(0,14);
      maze_update(0,15);
      */
    /*  for(i=0;i<16;i++)
     for(j=0;j<16;j++)
     {
                      maze_update(i,j);
                      }
      */
    c=maze_update(0,15,0);
    printf("\n(%d,%d)\n",c.x,c.y);   
    for(i=0;m[c.x][c.y].value!=0;i++)
    {
    c=maze_update(c.x,c.y,0);
    printf("\n(%d,%d)\n",c.x,c.y);
    }

      
   /* maze_update(0,14);
    maze_update(0,13);  
    maze_update(0,14);
    */
      
   //   *********************************
print_maze();
getchar();      
}      
      
      

