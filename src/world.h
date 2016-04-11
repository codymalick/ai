#ifndef _WORLD
#define _WORLD

#define NUM_M 3
#define NUM_C 3
#define NUM_TOTAL NUM_C+NUM_M
#define BOAT_CAP 2

typedef enum Person {
    CANNIBAL,
    MISSIONARY,
    NOBODY
} Person;

typedef enum Location {
    LEFT,
    RIGHT,
    BOAT
} Location;

class World {
    public:
        World();
        int count(Location, Person);
        void replace(Person from, Person to);
        int move(Location, Location, Person);
        
    private:
        Person left[NUM_TOTAL];
        Person right[NUM_TOTAL];
        Person boat[BOAT_CAP];
        
        Person* field_addr(Location);
        int field_len(Location);
};

#endif