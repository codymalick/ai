#ifndef _SOLVER
#define _SOLVER

#include "alg.h"
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

typedef void (*callback)(void); // function pointer type


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
        void set_queue(AlgQueue*);
        void bfs();
        inline bool is_solved() { return (solution != NULL); }
        vector<World*> ascend();
        inline int total_expanded() { return expanded; }
        
    private:
        Node *tree;
        Node *solution;
        World *end_state;
        AlgQueue *queue;
        signature to_signature(World*);
        set<signature>* visited;
        int expanded; // total expanded nodes
};

#endif
