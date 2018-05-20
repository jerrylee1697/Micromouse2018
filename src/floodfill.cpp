// //#include <iostream>
// #include <vector>
// #include <cmath>
// //#include<fstream>
// using namespace std;

// const int NORTH = 1;
// const int EAST = 2;
// const int SOUTH = 4;
// const int WEST = 8;   

// class Vertex {
//     public:
//         vector<Vertex*> adjacent;
//         vector<bool> walls = {false,false,false,false}; // N(0), E(1), S(2), W(3)
//         int distance;
//         bool visited; //has it been traversed yet?
//         int numWalls;
//         int position;
//     //Vertex();
//     //~Vertex();
// };

// //BEGIN GRAPH CLASS
// class Graph : public Vertex {
//     private:
//         vector<Vertex> vertices;
//       int mazeSize;
//       vector<Vertex*> stack;
//     public:
//         Graph(int);
//       void addEdge(Vertex*, int);
//       bool checkEdge(Vertex* currCell, int wall); //does it exist?
//       void updateDist();
//       void printGraph(Vertex*);
//       void populate(); //populate initial maze with distances
//       void initialize(); //add maze borders and adjacent vertices
//       void floodfill(int);
//       void addWalls(vector<int> rows);
// };

// Graph::Graph(int size) {
//     mazeSize = size;
//     vertices.resize(size * size);

// }
// void Graph::printGraph(Vertex* currCell) {
//   bool left = false;
//   bool right = false;
//   bool space = false;
//   bool beginL = false;
//   cout << "+";
//   for(int i = 0; i < mazeSize; ++i) {
//     if(this->vertices.at(i).walls.at(0) == true) { //print top wall
//         cout << "---+";
//     }
//   } cout << endl;
//   int test = 0;
//   for(int i = 0; i < mazeSize; ++i) {
//     left = false;
//     right = false;
//     space = false;
//     beginL = true;
//     cout << "|";
//     for(int j = 0; j < mazeSize; ++j) {
//       if(this->vertices.at(test).walls.at(3) == true && right == false && beginL == false) { //print left wall
//         cout << "|";
//         if(test == currCell->position) {cout << "@";}
//         else if(this->vertices.at(test).visited == true) {cout << "*";} 
//         else {cout << " ";}
//         cout << this->vertices.at(test).distance;
//         if(this->vertices.at(test).distance < 10) {cout << " ";}
//         //else if(this->vertices.at(test).distance > 9 && this->vertices.at(test).distance < 100) {cout << "  ";}
//         //else {cout << " ";}
//         left = true;
//       } 
      
//       else if(this->vertices.at(test).walls.at(1) == true && left == false && beginL == false) { //print right wall
//         if(right == false) {cout << " ";}
//         if(test == currCell->position) {cout << "@";}
//         else if(this->vertices.at(test).visited == true) {cout << "*";} 
//         else {cout << " ";}
//         cout << this->vertices.at(test).distance;
//         if(this->vertices.at(test).distance < 10) {cout << " ";}
//         //else if(this->vertices.at(test).distance >= 10 && this->vertices.at(test).distance < 100) {cout << "  ";}
//         //cout << " ";
//         cout << "|";
//         right = true;
//         space = true;
//       } else {
//         left = false;
//         if(space != true && beginL == false) {cout << " ";}
//         if(test == currCell->position) {cout << "@";}
//         else if(this->vertices.at(test).visited == true) {cout << "*";} 
//         else {cout << " ";}
//         cout << this->vertices.at(test).distance;
//         //if(this->vertices.at(test).distance < 10) {cout << "  ";}
//         if(this->vertices.at(test).distance <= 9) {cout << " ";}
//         //else {cout << "";}
//         right = false;
//         space = false;
//         }
        
//       ++test;
//       beginL = false;
//     }
//     cout << endl << "+";
//     for(int k = 0; k < mazeSize; ++k) {
//     if(this->vertices.at(test - mazeSize + k).walls.at(2) == true) {cout << "---+";}
//       else{cout << "   +";}
//     }cout << endl;
//   }
  
//   return;
// }
// void Graph::initialize() {
//   //set up borders around maze
//   for(int i = 0; i < mazeSize * mazeSize; ++i) {
//     this->vertices.at(i).position = i; //initialize position # in array
//     this->vertices.at(i).walls.resize(4);
//     this->vertices.at(i).numWalls = 0;
//     if((i - mazeSize) < 0) { //upper maze border
//       this->vertices.at(i).walls.at(0) = true;
//     }
//     if((i + mazeSize) >= (mazeSize * mazeSize)) { //lower maze border
//       this->vertices.at(i).walls.at(2) = true;
//     }
//     if((i % mazeSize) == 0) { //left maze border
//       this->vertices.at(i).walls.at(3) = true;
//     }
//     if((i + 1) % mazeSize == 0) { //right border
//       this->vertices.at(i).walls.at(1) = true;
//     }
//   }
//   //add lists of adjacent vertices
//   for(int i = 0; i < mazeSize * mazeSize; ++i) {
//     if(this->vertices.at(i).walls.at(0) == false) { //check upper
//       this->vertices.at(i).adjacent.push_back(&(this->vertices.at(i - mazeSize)));
//     }
//     if(this->vertices.at(i).walls.at(2) == false) { //check lower
//       this->vertices.at(i).adjacent.push_back(&(this->vertices.at(i + mazeSize)));
//     }
//     if(this->vertices.at(i).walls.at(3) == false) { //check left
//       this->vertices.at(i).adjacent.push_back(&(this->vertices.at(i - 1)));
//     }
//     if(this->vertices.at(i).walls.at(1) == false) { //check right
//       this->vertices.at(i).adjacent.push_back(&(this->vertices.at(i + 1)));
//     }
//   }
// }
// void Graph::populate() {
//   int num = mazeSize - 2;
//   int i = 0;
//   while(i < mazeSize * mazeSize) {
//     for(int a = num; a >= num / 2; --a) {
//       for(int j = a; j >= a - num / 2; --j) {
//         this->vertices.at(i).distance = j;
//         ++i;
//       }
//       for(int j = a - num/ 2; j <= a; ++j) {
//         this->vertices.at(i).distance = j;
//         ++i;
//       } cout << endl;
      
//     }
//     num = mazeSize - 2;
//     for (int a = num / 2; a <= num; ++a) {
      
//       for(int j = a; j >= a - num / 2; --j) {
//         this->vertices.at(i).distance = j;
//         ++i;
//       } 
//       for(int j = a - num / 2; j <= a; ++j) {
//         this->vertices.at(i).distance = j;
//         ++i;
//       }cout << endl;
      
//     }
//   } cout << endl;
// }
// void Graph::updateDist() {
//   int i = 0;
//   Vertex* top = this->stack.back();
//   Vertex* minimum = this->stack.back();

//   for(i = 0; i < top->adjacent.size(); ++i) {
//     if(top->adjacent.at(i)->distance < minimum->distance) {
//       minimum = top->adjacent.at(i);
//     }
//   } 
//   //for(i = 0; i < top->adjacent.size(); ++i) {cout << top->adjacent.at(i)->position << " ";}
//     if(top->distance != minimum->distance + 1 && top->distance != 0) { //are the distances correct?
//       top->distance = minimum->distance + 1;
//       this->stack.pop_back();
//       for(i = 0; i < top->adjacent.size(); ++i) {
//         this->stack.push_back(top->adjacent.at(i));
//       }
//     } else {this->stack.pop_back();}


// }
// void Graph::floodfill(Vertex currCell) {
//   //char key = ' ';
//  // Vertex* currCell = &(this->vertices.at(start));
//   currCell->visited = true;
//   Vertex* closest = currCell;
//   Vertex* toErase;
  
//  // while(key != 'z' && currCell->distance != 0) {
//     this->stack.clear();
//     //DEBUGGING
//     //for(int k = 0; k < currCell->adjacent.size(); k++) {cout << currCell->adjacent.at(k)->position << " ";} cout << endl;
//     //

//     //go through adjacnecy list of current cell to find non-visted cell with smallest distance
//     for(int i = 0; i < currCell->adjacent.size(); ++i) {
//       if(currCell->adjacent.at(i)->distance < closest->distance && !currCell->adjacent.at(i)->visited) {
//         closest = currCell->adjacent.at(i);
//       }
//     } 
//     //if there are no unvisited cells, choose the one with the smallest distance
//     if(closest == currCell) {
//       for(int i = 0; i < currCell->adjacent.size(); ++i) {
//       if(currCell->adjacent.at(i)->distance < closest->distance) {
//         closest = currCell->adjacent.at(i);
//       }
//       }
//     }

//     //DEBUGGING
//    // cout << "curr: " << currCell->position << endl;
//     //
    
//     currCell = closest;
//     currCell->visited = true;

//     //DEBUGGING
//    // cout << "next: " << currCell->position << endl;
//     //

//     //begin checking for new walls
//     int i = 0;
//     int k = 0;
//     //North
//     if(currCell->walls.at(0) == true && (currCell->position - mazeSize) > 0) { //North
//       this->stack.push_back(currCell);
//       this->stack.push_back(currCell-mazeSize);
//       for(i = 0; i < currCell->adjacent.size(); ++i) {
//         //cout << "N: " << currCell->adjacent.at(i)->position << ", " << (currCell + 1)->position << endl;
//         if(currCell->adjacent.at(i) == currCell - mazeSize) {
//           toErase = currCell->adjacent.at(i);
//         for(k = 0; k < toErase->adjacent.size(); ++k) {
//           if(toErase->adjacent.at(k) == currCell) {
//             break;
//           }
//         }
//         toErase->adjacent.erase(toErase->adjacent.begin()+k);
//         currCell->adjacent.erase(currCell->adjacent.begin() + i);
//         }
//       } 
//     } 
//     //East
//     if(currCell->walls.at(1) == true && ((currCell->position + 1) % mazeSize) != 0) { //East
//       this->stack.push_back(currCell); //push current cell to stack
//       this->stack.push_back(currCell + 1); //push eastern cell to stack
//       for(i = 0; i < currCell->adjacent.size(); ++i) {
//         //DEBUGGING
//        // cout << "E: " << currCell->adjacent.at(i)->position << ", " << (currCell + 1)->position << endl;
//         //
//         //erase cells from eachother's adjaceny lists
//         if(currCell->adjacent.at(i) == currCell + 1) {
//           toErase = currCell->adjacent.at(i);
//           for(k = 0; k < toErase->adjacent.size(); ++k) {
//             if(toErase->adjacent.at(k) == currCell) {
//               break;
//             }
//           }
//           toErase->adjacent.erase(toErase->adjacent.begin()+k);
//           currCell->adjacent.erase(currCell->adjacent.begin() + i);
          
//         }
//       }
      
//     }
//     //South
//     if(currCell->walls.at(2) == true && (currCell->position + mazeSize) < mazeSize*mazeSize) { //South
//       this->stack.push_back(currCell); //push current cell to stack
//       this->stack.push_back(currCell + mazeSize); //push southern cell to stack
//       for(i = 0; i < currCell->adjacent.size(); ++i) {
//         //DEBUGGING
//        // cout << "S: " << currCell->adjacent.at(i)->position << ", " << (currCell + mazeSize)->position << endl;
//         //
//         if(currCell->adjacent.at(i) == currCell + mazeSize) { //find the southern cell in adjacency list and mark it for erasing
//           toErase = currCell->adjacent.at(i);
//           for(k = 0; k < toErase->adjacent.size(); ++k) {
//             if(toErase->adjacent.at(k) == currCell) {
//               break;
//             }
//           }
//           toErase->adjacent.erase(toErase->adjacent.begin()+k);
//           currCell->adjacent.erase(currCell->adjacent.begin() + i);
//         }
//       } 
//     }
//     //West
//     if(currCell->walls.at(3) == true && (currCell->position % mazeSize) != 0) { //West
//       //for(int a = 0; a < 4; ++a) {cout << "HERE: " << currCell->walls.at(a) << endl;}
//       this->stack.push_back(currCell);
//       this->stack.push_back(currCell - 1);
//       for(i = 0; i < currCell->adjacent.size(); ++i) {
//         //cout << "W: " << currCell->adjacent.at(i)->position << ", " << (currCell + 1)->position << endl;
//         if(currCell->adjacent.at(i) == currCell - 1) {
//           toErase = currCell->adjacent.at(i);
//         for(k = 0; k < toErase->adjacent.size(); ++k) {
//           if(toErase->adjacent.at(k) == currCell) {
//             break;
//           }
//         }
//         toErase->adjacent.erase(toErase->adjacent.begin()+k);
//         currCell->adjacent.erase(currCell->adjacent.begin() + i);
//         }
//       } 
//     }
//     //
//    // this->printGraph(currCell);
//     //cout << "STACK SIZE:" << this->stack.size() << endl;
//     //cout << "adjacent cells: ";
//     //for(int k = 0; k < currCell->adjacent.size(); k++) {
//       //cout << currCell->adjacent.at(k)->position << " ";
//     //} cout << endl;

//    // cout << "stack: ";
//     //if (this->stack.size() != 0) {cout << this->stack.back()->position << " ";}
//     //cout << endl << endl;
//     //cout << "TEST: ";
//     //
    
//     //if (this->stack.size() != 0) {
//       //for(int i = 0; i < stack.size(); ++i) {
//       //  cout << this->stack.at(i)->position << " ";}
//     //  } cout << endl;
    
//     while(this->stack.size() != 0) {
//       this->updateDist();
//     }
// return currCell;
    
// /*cout << endl;
// int test = 0;
//     for(int i = 0; i < this->mazeSize; ++i) { //printing 1 - 255
//     for(int j = 0; j < this->mazeSize; ++j) {
//       cout << test;
//       if(test < 10) {cout << "   ";}
//       else if(test > 9 && test < 100) {cout << "  ";}
//       else {cout << " ";}
//       ++test;
//     }
//     cout << endl << endl;
//   } cout << endl;*/
//   //  cout << "Enter any key to continue ('z' to quit): " << endl;
//     //cin >> key;
//   // }
// }
// void Graph::addEdge(Vertex* currCell, int wall) {
//   if(currCell != 0) {
//     currCell->walls.at(wall) = true;
//   }
// }

// bool Graph::checkEdge(Vertex* currCell, int wall){
//   if(currCell != 0){
//     if(currCell->walls.at(wall) == 1){
//       return true;
//     }
//     return false;
//   }
//   return false;
// }
// /*
// void Graph::addWalls(vector<int> rows){ //FOR TESTING: adds walls from example maze
//   for(int i = 0; i < rows.size(); ++i){
//     int num = rows.at(i);
//     Vertex* curCell = &(this->vertices.at(i));
//     curCell->numWalls = num;
//     curCell->walls.resize(4);
//     curCell->visited = false;
//     if(num == NORTH){
//       curCell->walls.at(0) = 1;
//     }else if(num == EAST){
//       curCell->walls.at(1) = 1;
//     }else if(num == SOUTH){
//       curCell->walls.at(2) = 1;
//     }else if(num == WEST){
//       curCell->walls.at(3) = 1;
//     }else if(num == NORTH + EAST){
//       curCell->walls.at(0) = 1;
//       curCell->walls.at(1) = 1;
//     }else if(num == NORTH + SOUTH){
//       curCell->walls.at(0) = 1;
//       curCell->walls.at(2) = 1;
//     }else if(num == SOUTH + EAST){
//       curCell->walls.at(1) = 1;
//       curCell->walls.at(2) = 1;
//     }else if(num == NORTH + SOUTH + EAST){
//       curCell->walls.at(0) = 1;
//       curCell->walls.at(1) = 1;
//       curCell->walls.at(2) = 1;
//     }else if(num == NORTH + WEST){
//       curCell->walls.at(0) = 1;
//       curCell->walls.at(3) = 1;
//     }else if(num == EAST + WEST){
//       curCell->walls.at(1) = 1;
//       curCell->walls.at(3) = 1;
//     }else if(num == NORTH + EAST + WEST){
//       curCell->walls.at(0) = 1;
//       curCell->walls.at(1) = 1;
//       curCell->walls.at(3) = 1;
//     }else if(num == SOUTH + WEST){
//       curCell->walls.at(2) = 1;
//       curCell->walls.at(3) = 1;
//     }else if(num == NORTH + SOUTH + WEST){
//       curCell->walls.at(0) = 1;
//       curCell->walls.at(2) = 1;
//       curCell->walls.at(3) = 1;
//     }else if(num == EAST + SOUTH + WEST){
//       curCell->walls.at(1) = 1;          
//       curCell->walls.at(2) = 1;
//       curCell->walls.at(3) = 1;
//     }
//   }
// }*/
// /*  Vertex* closest = currCell->adjacent.at(0);
//   for(int i = 1; i < currCell->adjacent.size(); ++i) {
//       if(currCell->adjacent.at(i)->distance < closest->distance) {
//         closest = currCell->adjacent.at(i);
//       }
//     }

// }*/
// /*
// int main(int argc, char* argv[]) {
//   int size;

//   cout << "Enter size of maze: " << endl;
//   cin >> size;

//   Graph maze(size);
//   int test = 0;

//   for(int i = 0; i < size; ++i) { //printing 1 - 255
//     for(int j = 0; j < size; ++j) {
//       cout << test;
//       if(test < 10) {cout << "   ";}
//       else if(test > 9 && test < 100) {cout << "  ";}
//       else {cout << " ";}
//       ++test;
//     }
//     cout << endl << endl;
//   } cout << endl;
  
//   string myfile;
//     vector<int> data;
//   if(argc == 2) { //if a file is entered as a command line argument
//         myfile = argv[1];
//         ifstream fin;
//         fin.open(myfile.c_str());
//         if(fin.is_open()) {
//             int num = 0;
//             while(fin >> num) {
//                 data.push_back(num);
//             } // while
//             fin.close();
//         } // if
//     } // if

//   maze.populate();
//   maze.initialize();
//   maze.addWalls(data);
//   //maze.printGraph();

//   int start = 0;
//   cout << "Enter starting cell: " << endl;
//   cin >> start;
//   maze.floodfill(start);

//   return 0;
// }*/