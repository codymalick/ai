#ifndef _AUX
#define _AUX

#define USAGE "Use: ai_mc <initial state file> <goal state file> <mode> <output file>"

#include "world.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

int flag_check(int, char **);
string read_file(char **);
World* world_from_string(string);
void state_vector_print(vector<World*>);

#endif