/***************************************
 * Authors: Andrew Tolvstad, Cody Malick
 * CS 331, Implementation Assignment 1
 * main.cpp
 **************************************/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>

//#include "world.h"
//#include "alg.h"

using std::cout;
using std::endl;
using std::cerr;

int flag_check(int argc, char *argv[]);

#define USAGE "Use: ai_mc <initial state file> <goal state file> <mode> <output file>"

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
    }
    if(!strcmp(mode, "dfs")) {
        cout << "Running Depth-First Search" << endl;
        //dfs();
    }
    if(!strcmp(mode, "iddfs")) {
        cout << "Running Iterative Deepening Depth-First Search" << endl;
        //iddfs();
    }
    if(!strcmp(mode, "astar")) {
        cout << "Running A-Star Search" << endl;
        //astar();
    } else {
        cout << "Invalid mode" << endl;
        cout << USAGE << endl;
        exit(1);
    }
    
    
    
    exit(0);
}

int flag_check(int argc, char *argv[])
{
    //debug mode
    if(argc == 2 && strcmp(argv[1], "-d")) {
        return 0;
    }
    // Check argument count is correct
    if(argc !=   4) {
        cout << "Invalid number of arguments" << endl;
        cout << USAGE << endl;
        return 1;
    }
    
    // Check initial state file is valid
    if(!std::ifstream(argv[1])) {
        cout << "Initial State file invalid" << endl;
        return 1;
    }
    
    // Check goal state file
    if(!std::ifstream(argv[2])) {
        cout << "Goal State file invalid" << endl;
        return 1;
    }
    
    // Check mode
    
    // Check output? Do we need to check or just assume overwrite behavior?
    
    // Success
    return 0;
}

