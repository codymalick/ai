#include "aux.h"
#include "world.h"

#include <iostream>
#include <cstring>
#include <fstream>

using std::cout;
using std::endl;

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

/* char* read_file(char *filename[]) {
   char *source[];
   std::getline(std::fstream(filename), source);
   std::cout << source << std::endl;
    
} */

World* world_from_string(const char* source) {
    
}
