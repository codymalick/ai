#ifndef _AUX
#define _AUX

#define USAGE "Use: ai_mc <initial state file> <goal state file> <mode> <output file>"

#include "world.h"
#include <string>

int flag_check(int, char **);
std::string read_file(char **);
World* world_from_string(std::string);

#endif