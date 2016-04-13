#ifndef _AUX
#define _AUX

#define USAGE "Use: ai_mc <initial state file> <goal state file> <mode> <output file>"

int flag_check(int argc, char *argv[]);
char* read_file(char *file[]);
//*int read_goal(char *goal_file[]);

#endif