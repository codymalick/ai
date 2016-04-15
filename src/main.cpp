/***************************************
 * Authors: Andrew Tolvstad, Cody Malick
 * CS 331, Implementation Assignment 1
 * main.cpp
 **************************************/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>

#include "world.h"
#include "alg.h"
#include "aux.h"
#include "solver.h"

using std::cout;
using std::endl;
using std::cerr;
using std::string;


int main(int argc, char *argv[]) {

    //Arguements are in the following format:
    // main.o <initial state file> <goal state file> <mode> <output file>

    if(flag_check(argc, argv))
        exit(1);
    
    Solver* solver;
    
    {
        string start_string = read_file(&argv[1]);
        string goal_string = read_file(&argv[2]);
        
        cout << "Creating worlds..." << endl;
        World* w1 = world_from_string(start_string);
        World* w2 = world_from_string(goal_string);
        
        cout << "Creating solver..." << endl;
        solver = new Solver(w1, w2);
    }
    
    const char *mode = argv[3];
    //Enum names defined by assignment requirements
    
    if(!strcmp(mode, "bfs")) {
        cout << "Running Breadth-First-Search" << endl;
        solver->bfs();
    } else if(!strcmp(mode, "dfs")) {
        cout << "Running Depth-First Search" << endl;
        //dfs();
    } else if(!strcmp(mode, "iddfs")) {
        cout << "Running Iterative Deepening Depth-First Search" << endl;
        //iddfs();
    } else if(!strcmp(mode, "astar")) {
        cout << "Running A* Search" << endl;
        //astar();
    } else {
        cout << "Invalid mode" << endl;
        cout << USAGE << endl;
        return 1;
    }
    
    if(solver->is_solved()) {
        cout << "Solution found:" << endl;
        state_vector_print(solver->ascend());
    } else {
        cout << "No solutions found :(" << endl;
    }
    
    cout << "Total expanded nodes: " << solver->total_expanded() << endl;

    delete solver;
    
    return 0;
}
