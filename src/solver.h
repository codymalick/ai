#ifndef _SOLVER
#define _SOLVER

#include "alg.h"
#include "world.h"

#include <vector>

using std::vector;

typedef void (*callback)(void); // function pointer type

class AlgQueue; // forward declaration for circular include

class Node {
    public:
        Node(Node*, World*);
        ~Node();
        void enchild();
    
    private:
        World *val;
        Node *parent;
        
        //Set of Children
        int child_count;
        Node** child;
};

class Solver {
    public:
        Solver(World*, World*);
        // vector<World*> solve(AlgQueue*, callback);
    private:
        Node *tree;
        World* end_state;
        AlgQueue* queue;
};

#endif