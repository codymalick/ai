#include "solver.h"
#include <cassert>

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
    queue = (AlgQueue*) NULL;
    solution = NULL;
}

void Solver::bfs() {
    queue = new BfsQueue;
    // visited = new unordered_map<tuple<int, int, Side>, bool>;
    expanded = 0;
    if(*(tree->val) == *end_state) {
        solution = tree;
        expanded++;
        return;
    }
    
    queue->push(tree); // Add root to queue
    vector<Node*> succ; // successors to current node
    Node* n;
    World* temp;
    
    while(true) {
        // get next node
        n = queue->pop();
        if(!n) return; // no more nodes in queue
        // -------- DEBUG PRINT --------
        std::cout << *(n->val) << std::endl;
        if(*(n->val) == *end_state) {
            solution = n;
            return;
        }
        expanded++;
        
        
        // generate successors
        // one missionary to boat
        if(n->val->is_legal_move(MISSIONARY, n->val->boat_closest(), BOAT)) {
            temp = new World(*(n->val));
            temp->move(MISSIONARY, temp->boat_closest(), BOAT);
            succ.push_back(new Node(n, temp));
        
            // two missionaries to boat
            if(temp->is_legal_move(MISSIONARY, n->val->boat_closest(), BOAT)) {
                temp = new World(*temp); // new copy of previous temp
                temp->move(MISSIONARY, temp->boat_closest(), BOAT);
                succ.push_back(new Node(n, temp));
            }
        }
        // one cannibal to boat
        if(n->val->is_legal_move(CANNIBAL, n->val->boat_closest(), BOAT)) {
            temp = new World(*(n->val));
            temp->move(CANNIBAL, temp->boat_closest(), BOAT);
            succ.push_back(new Node(n, temp));
        }
        
        // one cannibal, one missionary to boat
        if(n->val->is_legal_move(CANNIBAL, n->val->boat_closest(), BOAT)) {
            temp = new World(*(n->val));
            temp->move(CANNIBAL, temp->boat_closest(), BOAT);
            if(temp->is_legal_move(MISSIONARY, n->val->boat_closest(), BOAT)) {
                temp->move(MISSIONARY, temp->boat_closest(), BOAT);
                succ.push_back(new Node(n, temp));
            } else {
                delete temp;
            }
        }
        
        // two cannibals to boat
        if(n->val->is_legal_move(CANNIBAL, n->val->boat_closest(), BOAT)) {
            temp = new World(*(n->val));
            temp->move(CANNIBAL, temp->boat_closest(), BOAT);
            if(temp->is_legal_move(CANNIBAL, n->val->boat_closest(), BOAT)) {
                temp->move(CANNIBAL, temp->boat_closest(), BOAT);
                succ.push_back(new Node(n, temp));
            } else {
                delete temp;
            }
        }
        
        
        // remove failure states
        for(std::vector<Node*>::iterator it = succ.begin(); it < succ.end(); ++it)
            if((*it)->val->fail()) {
                delete *it;
                it = succ.erase(it);
            }
        
        // put successor nodes into tree
        n->child_count = succ.size();
        n->child = new Node*[n->child_count];
        
        for(int i=0; i<succ.size(); i++)
            n->child[i] = succ[i];
        
        succ.clear();
        
        // put child nodes into queue, checking for solution
        for(int i=0; i<n->child_count; i++) {
            if(*(n->child[i]->val) == *end_state) {
                solution = n->child[i];
                return;
            }
            queue->push(n->child[i]);
        }
    }
}
        
vector<World*> Solver::ascend() {
    assert(solution);
    
    vector<World*> v;
    Node* current = solution;
    
    while(current) {
        v.push_back(current->val);
        current = current->parent;
    }
    
    return v;
}