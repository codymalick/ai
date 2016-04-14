#include "solver.h"

Node::Node(Node* parent, World* val) {
    this->val = val;
    this->parent = parent;
    child = (Node**) NULL;
}

Node::~Node() {
    for(int i=0; i<child_count; i++) delete child[i];
    delete val;
}

Solver::Solver(World* start, World* end) {
    tree = new Node((Node*) NULL, start);
    end_state = end;
}

/*vector<World*> solve(AlgQueue* queue, callback algo) {
    return NULL;
}*/