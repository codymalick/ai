#include <iostream>
#include "world.h"

using std::cout;
using std::endl;

int main() {
    cout << "Initialize world." << endl;
    World w;
    cout << w << endl;
   
    cout << "Move missionary to boat." << endl; 
    w.move(MISSIONARY, LEFT_SHORE, BOAT);
    cout << w << endl;
    
    cout << "Can boat move? " << (w.boat_can_move()?"Yes":"No") << endl;
    if(w.boat_can_move()) {
        cout << "Moving boat..." << endl;
        w.boat_move();
    }
    cout << w << endl;
    
    cout << "Missionary get out." << endl;
    w.move(MISSIONARY, BOAT, RIGHT_SHORE);
    cout << w << endl;
    
    cout << "Illegal operation." << endl;
    int result = w.is_legal_move(CANNIBAL, RIGHT_SHORE, BOAT);
    cout << "Illegal op result: " << result << endl;
    
    return 0;
}