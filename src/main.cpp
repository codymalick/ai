/***************************************
 * Authors: Andrew Tolvstad, Cody Malick
 * CS 331, Implementation Assignment 1
 * main.cpp
 **************************************/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>

#include "world.h"
#include "alg.h"
#include "aux.h"

using std::cout;
using std::endl;
using std::cerr;


int main(int argc, char *argv[]) {

    //Arguements are in the following format:
    // main.o <initial state file> <goal state file> <mode> <output file>

    if(flag_check(argc, argv))
        exit(1);
    
    char *mode = argv[3];
    //Enum names defined by assignment requirements
    
    if(!strcmp(mode, "bfs")) {
        cout << "Running Breadth-First-Search" << endl;
        //bfs();
    } else if(!strcmp(mode, "dfs")) {
        cout << "Running Depth-First Search" << endl;
        //dfs();
    } else if(!strcmp(mode, "iddfs")) {
        cout << "Running Iterative Deepening Depth-First Search" << endl;
        //iddfs();
    } else if(!strcmp(mode, "astar")) {
        cout << "Running A-Star Search" << endl;
        //astar();
    } else {
        cout << "Invalid mode" << endl;
        cout << USAGE << endl;
        exit(1);
    }
    
    
    
    exit(0);
}
