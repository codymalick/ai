#ifndef _SOLVER
#define _SOLVER

#include "alg.h"
#include "aux.h"
class AlgQueue; // forward declaration for circular include

#include "world.h"

#include <vector>
#include <tuple>
#include <set>

using std::vector;
using std::tuple;
using std::set;
// miss-left, can-left, miss-right, can-right, boat side
typedef tuple<int, int, int, int, Side> signature;

class Node {
    public:
        Node(Node*, World*);
        ~Node();
        
        World *val;
        Node *parent;
        int child_count;
        Node **child;
};

class Solver {
    public:
        Solver(World*, World*);
        ~Solver();
        void reset();
        
        bool solve(Algo, int);
        inline void solve(Algo a) { solve(a, 0); }
        
        void set_queue(AlgQueue*);
        inline bool is_solved() { return (solution != NULL); }
        vector<World*> ascend();
        inline int total_expanded() { return expanded; }
        int depth(Node*);
        
    private:
        Node *tree;
        Node *solution;
        World *start_state;
        World *end_state;
        AlgQueue *queue;
        signature to_signature(World*);
        set<signature>* visited;
        int expanded; // total expanded nodes
};

#endif
