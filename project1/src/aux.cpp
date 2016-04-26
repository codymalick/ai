#include "aux.h"
#include "world.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>


using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stoi;
using std::vector;
using std::strtok;
using std::istreambuf_iterator;

Algo alg_type(const char* s) {
    if(!strcmp(s, "bfs"))
        return BFS;
    
    if(!strcmp(s, "dfs"))
        return DFS;
    
    if(!strcmp(s, "iddfs"))
        return IDDFS;
    
    if(!strcmp(s, "astar"))
        return ASTAR;
    
    return BAD_ALG;
}

int flag_check(int argc, char **argv)
{

    // Check argument count is correct
    if(argc !=   5) {
        cout << "Invalid number of arguments" << endl;
        cout << USAGE << endl;
        return 1;
    }
    
    // Check initial state file is valid
    if(!ifstream(argv[1])) {
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

string read_file(char **filename) {
    ifstream f(*filename);
    string s((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    f.close();
    
    return s;
}

World* world_from_string(string s) {
    // file arrangement is static, so we can expect things to be deterministic
    // in location. Manually taking line 1[1-3] and line2[1-3] works

    char *input = (char*) s.c_str();
    *strchr(input, '\n') = ',';
    
    char *token = strtok(input, ",");
    int tray[5];
    for(int i=0; i<5; i++) {
        tray[i] = atoi(token);
        token = strtok(NULL, ",");
    }   
    
    return new World(
        tray[0], // left missionary
        tray[1], // left cannibal
        tray[3], // right missionary
        tray[4], // right cannibal
        (tray[2] == 1)?LEFT_SIDE:RIGHT_SIDE
    );
}

void state_vector_print(vector<World*> v, char** filename) {
    ofstream f(*filename);
    for(int i=v.size()-1; i>=0; i--) {
        cout << *(v[i]) << endl;
        f << *(v[i]) << endl;
    }
    f.close();
    
    cout << "Solution is " << v.size() << " moves." << endl;
}