#ifndef _WORLD
#define _WORLD

#include <iostream>

#define NUM_M 3
#define NUM_C 3
#define NUM_TOTAL NUM_C+NUM_M
#define BOAT_CAP 2

enum Person {
    CANNIBAL,
    MISSIONARY,
    NOBODY
};

std::ostream& operator<<(std::ostream&, const Person&);

enum Location {
    LEFT_SHORE,
    RIGHT_SHORE,
    BOAT
};

enum Side {
    LEFT_SIDE,
    RIGHT_SIDE
};

class World {
    public:
        World();
        int count(Location, Person);
        int count(Side, Person);
        int is_legal_move(Person, Location, Location);
        void move(Person, Location, Location);
        bool boat_can_move();
        void boat_move();
        
        friend std::ostream& operator<<(std::ostream&, const World&);
        
    private:
        Person left[NUM_TOTAL];
        Person right[NUM_TOTAL];
        Person boat[BOAT_CAP];
        Side boat_side;
        
        Person* field_addr(Location);
        int field_len(Location);
};

#endif