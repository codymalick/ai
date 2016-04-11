#include "world.h"

World::World() {
    for (int i = 0; i < NUM_TOTAL; i++) {
        left[i] = (i < NUM_M) ? MISSIONARY : CANNIBAL;
        right[i] = NOBODY;
    }

    for (int i=0; i<BOAT_CAP; i++)
        boat[i] = NOBODY;
}

int World::count(Location location, Person type) {
    Person * set = field_addr(location);
    int count = field_len(location);
    int sum = 0;

    for (int i=0; i<count; i++)
        if (set[i] == type)
            sum++;

    return sum;
}

int World::move(Location from, Location to, Person type) {
    // failure conditions
    if(from != BOAT && to != BOAT) return -1; // Illegal move
    if(this->count(from, type) < 1) return -2; // not enough people
    if(this->count(to, NOBODY) < 1) return -3; // no room

    Person *set;
    int count;
    
    // remove from 'from'
    set = field_addr(from);
    count = field_len(from);
    for(int i=0; i<count; i++)
        if(set[i] == type) {
            set[i] = NOBODY;
            break;
        }

    // add to 'to'
    set = field_addr(to);
    count = field_len(to);
    for(int i=0; i<count; i++)
        if(set[i] == NOBODY) {
            set[i] = type;
            break;
        }
    
    return 0;
}

Person* World::field_addr(Location location) {
    switch (location) {
        case LEFT:
            return this->left;
        case RIGHT:
            return this->right;
        case BOAT:
            return this->boat;
    }
}

int World::field_len(Location location) {
    switch (location) {
        case LEFT:
        case RIGHT:
            return NUM_TOTAL;
        case BOAT:
            return BOAT_CAP;
    }
}