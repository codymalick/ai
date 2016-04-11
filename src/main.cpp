/***************************************
 * Authors: Andrew Tolvstad, Cody Malick
 * CS 331, Implementation Assignment 1
 * main.cpp
 **************************************/

#include <iostream>
#include <stdlib.h>
//#include "world.h"
//#include "alg.h"

using std::cout;
using std::endl;
using std::cerr;

int flag_check(int argc, char *argv[]);

int main(int argc, char *argv[]) {

    //Arguements are in the following format:
    // main.o <initial state file> <goal state file> <mode> <output file>

    if(!flag_check(argc, argv))
        exit(1);
    
        
    cout << "Hello world!" << endl;
    return 0;
}

int flag_check(int argc, char *argv[])
{
    // Check argument count is correct
    if(argc != 4) {
        cout << "Invalid number of arguments" << endl;
        cout << "Use: ai_mc <initial state file> <goal state file> <mode> <output file>" << endl;
        return 1;
    }
    
    // Check initial state file is valid
    /*if(!std::ifstream(argv[1])) {
        cout << "Initial State file invalid" << endl;
        return 1;
    }*/
    
    // Check goal state file
    
    return 0;
}