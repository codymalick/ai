#include "world.h"
#include "alg.h"
#include "aux.h"
#include "solver.h"

int main() {
    {
        Solver* solver;
        {
            World* a = new World(0,0,3,3,LEFT_SIDE);
            World* b = new World(3,3,0,0,RIGHT_SIDE);
            
            solver = new Solver(a, b);
        }
        
        solver->solve(BFS);
        delete solver;
    }
    return 0;
}