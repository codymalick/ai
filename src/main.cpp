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
    
    Algo mode = alg_type(argv[3]);
    switch(mode) {
        case BFS:
            cout << "Running Breadth-First-Search" << endl;
            solver->solve(BFS);
            break;
            
        case DFS:
            cout << "Running Depth-First Search" << endl;
            solver->solve(DFS);
            break;
            
        case IDDFS: {
            cout << "Running Iterative Deepening Depth-First Search" << endl;
            int depth = 1;
            // if solver does not return true, i.e. yes run again, break
            while(solver->solve(IDDFS, depth)) {
                depth *= 2;
                solver->reset();
            }
            break;
        }
            
        case ASTAR:   
            cout << "Running A* Search" << endl;
            solver->solve(ASTAR);
            break;
        
        default:
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
