#ifndef _ALG
#define _ALG

#include "aux.h"
#include "solver.h"
class Node; // forward declaration for circular include

#include <deque>
#include <queue>
#include <stack>
#include <tuple>
#include <climits>



//Parent class for algorithm data structures
class AlgQueue {
    public:
        virtual ~AlgQueue() { }
        inline virtual void push(Node*) = 0;
        inline virtual void push(Node*, unsigned int) = 0;
        inline virtual Node* pop() = 0;
};

// queue
class BfsQueue : public AlgQueue {
    private:
        std::queue<Node*, std::deque<Node*>> data;
    public:
        ~BfsQueue() { }
        inline void push(Node* n) { data.push(n); }
        inline void push(Node* n, unsigned int p) { data.push(n); }
        inline Node* pop() {
            if(data.size() < 1) return NULL;
            Node* n = data.front();
            data.pop();
            return n;
        }
};

// stack
class DfsQueue : public AlgQueue {
    private:
        std::stack<Node*, std::deque<Node*>> data;
    public:
        ~DfsQueue() { }
        inline void push(Node* n) { data.push(n); }
        inline void push(Node* n, unsigned int p) { data.push(n); }
        inline Node* pop() {
            if(data.size() < 1) return NULL;
            Node* n = data.top();
            data.pop();
            return n;
        }
};

typedef std::tuple<Node*, unsigned int> prinode;

class PrinodeComparator {
    public:
        bool operator()(const prinode&, const prinode&) const;
};

// priority queue
class AstarQueue : public AlgQueue {
    private:
        std::priority_queue<prinode, std::deque<prinode>, PrinodeComparator> data;
    public:
        ~AstarQueue() { }
        inline void push(Node* n) { data.push(std::forward_as_tuple(n, UINT_MAX)); }
        inline void push(Node* n, unsigned int p) { data.push(std::forward_as_tuple(n, p)); }
        inline Node* pop() {
            if(data.size() < 1) return NULL;
            Node* n = std::get<0>(data.top());
            data.pop();
            return n;
        }
};

#endif