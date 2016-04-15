#include "solver.h"
#include <cassert>

Node::Node(Node* parent, World* val) {
    this->val = val;
    this->parent = parent;
    child_count = 0;
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
    visited = new set<signature>;
}

Solver::~Solver() {
    delete visited;
    if(queue) delete queue;
    if(tree) delete tree;
}

signature Solver::to_signature(World* w) {
    return std::make_tuple(
        w->count(LEFT_SHORE, MISSIONARY),
        w->count(LEFT_SHORE, CANNIBAL),
        w->count(RIGHT_SHORE, MISSIONARY),
        w->count(RIGHT_SHORE, CANNIBAL),
        w->get_boat_side()
    );
}

void Solver::bfs() {
    queue = new BfsQueue;
    
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
         
        // put into visited set
        visited->insert(to_signature(n->val));
        
        
        if(*(n->val) == *end_state) {
            solution = n;
            return;
        }
        // tracking number of expanded nodes
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
        
        // Move the boat
        if(n->val->boat_can_move()) {
            temp = new World(*(n->val));
            temp->boat_move();
            succ.push_back(new Node(n, temp));
        }
        
        // Move first person out of boat
        if(n->val->boat_at(0) != NOBODY) {
            temp = new World(*(n->val));
            temp->move(temp->boat_at(0), BOAT, temp->boat_closest());
            succ.push_back(new Node(n, temp));
        }
        
        // Move second person out of boat
        if(n->val->boat_at(1) != NOBODY) {
            temp = new World(*(n->val));
            temp->move(temp->boat_at(0), BOAT, temp->boat_closest());
            succ.push_back(new Node(n, temp));
        }
        // Move both out of boat
        if(n->val->boat_at(0) != NOBODY && n->val->boat_at(1) != NOBODY) {
            temp = new World(*(n->val));
            temp->move(temp->boat_at(0), BOAT, temp->boat_closest());
            temp->move(temp->boat_at(1), BOAT, temp->boat_closest());
            succ.push_back(new Node(n, temp));
        }
        
        // put successor nodes into tree if not failure or already seen
        for(vector<Node*>::iterator it = succ.begin(); it != succ.end(); )
            if((*it)->val->fail() || visited->find(to_signature((*it)->val)) != visited->end()) {
                delete *it;
                it = succ.erase(it);
            } else {
                ++it;
            }
            
        n->child_count = succ.size();
        n->child = new Node*[n->child_count];
        for(int i=0; i<n->child_count; i++)
            n->child[i] = succ[i];
        
        succ.clear();
        
        // put child nodes into queue
        for(int i=0; i<n->child_count; i++)
            queue->push(n->child[i]);
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