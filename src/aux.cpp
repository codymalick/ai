#include "aux.h"
#include "world.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::stoi;

int flag_check(int argc, char **argv)
{

    // Check argument count is correct
    if(argc !=   5) {
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
    
    // Success
    return 0;
}

std::string read_file(char **filename) {
    std::ifstream f(*filename);
    std::string s((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();
    
    return s;
}

World* world_from_string(std::string s) {
    // file arrangement is static, so we can expect things to be deterministic
    // in location. Manually taking line 1[1-3] and line2[1-3] works
    return new World(
        s[0]-'0', // left missionary
        s[6]-'0', // left cannibal
        s[2]-'0', // right missionary
        s[8]-'0', // right cannibal
        (s[4]-'0' == 1)?LEFT_SIDE:RIGHT_SIDE
    );
}
