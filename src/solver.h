#ifndef _SOLVER
#define _SOLVER

#include "alg.h"
class AlgQueue; // forward declaration for circular include
#include "world.h"

#include <vector>
#include <tuple>
#include <unordered_map>

using std::vector;
using std::tuple;
using std::unordered_map;

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
        // vector<World*> solve(AlgQueue*, callback);
        void set_queue(AlgQueue*);
        void bfs();
        inline bool is_solved() { return (solution != NULL); }
        vector<World*> ascend();
        
    private:
        Node *tree;
        Node *solution;
        World *end_state;
        AlgQueue *queue;
        unordered_map<int[5], bool>* visited;
        int expanded; // total expanded nodes
};

namespace std {
    template <> struct hash<int [5]> {
        std::size_t operator()(const int& [5]) const;
    };
}

#endif
