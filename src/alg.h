#ifndef _ALG
#define _ALG

#include "solver.h"
class Node; // forward declaration for circular include

#include <deque>
#include <queue>
#include <stack>
#include <tuple>
#include <climits>

typedef std::tuple<Node*, unsigned int> prinode;
auto node_cmp = [](prinode a, prinode b) {
    return std::get<1>(a) > std::get<1>(b);
};

//Parent class for algorithm data structures
class AlgQueue {
    public:
        inline virtual void push(Node*) = 0;
        inline virtual void push(Node*, unsigned int) = 0;
        inline virtual Node* pop() = 0;
};

// queue
class BfsQueue : public AlgQueue {
    private:
        std::queue<Node*, std::deque<Node*>> data;
    public:
        inline void push(Node* n) { data.push(n); }
        inline void push(Node* n, unsigned int p) { data.push(n); }
        inline Node* pop() {
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
        inline void push(Node* n) { data.push(n); }
        inline void push(Node* n, unsigned int p) { data.push(n); }
        inline Node* pop() {
            Node* n = data.top();
            data.pop();
            return n;
        }
};

// priority queue
class AstarQueue : public AlgQueue {
    private:
        std::priority_queue<prinode, std::deque<prinode>, decltype(node_cmp)> data;
    public:
        inline void push(Node* n) { data.push(std::forward_as_tuple(n, UINT_MAX)); }
        inline void push(Node* n, unsigned int p) { data.push(std::forward_as_tuple(n, p)); }
        inline Node* pop() {
            Node* n = std::get<0>(data.top());
            data.pop();
            return n;
        }
};

#endif