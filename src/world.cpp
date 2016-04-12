#include "world.h"
#include <iostream>
#include <assert.h>

World::World() {
    for(int i=0; i<NUM_TOTAL; i++) {
        left[i] = (i<NUM_M)?MISSIONARY:CANNIBAL;
        right[i] = NOBODY;
    }

    for(int i=0; i<BOAT_CAP; i++)
        boat[i] = NOBODY;
    
    boat_side = LEFT_SIDE;
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

int World::count(Side side, Person type) {
    int sum;
    
    if(side == LEFT_SIDE) {
        sum = count(LEFT_SHORE, type);
    } else {
        sum = count(RIGHT_SHORE, type);
    }
    
    if(boat_side == side)
        sum += count(BOAT, type);
    
    return sum;
}
    
// TODO: throw exception?
int World::is_legal_move(Person type, Location from, Location to) {
    if((from != BOAT && to != BOAT) || from == to) return -1; // Must include boat
    if(((boat_side == LEFT_SIDE) && (from == RIGHT_SHORE || to == RIGHT_SHORE)) || \
       ((boat_side == RIGHT_SIDE) && (from == LEFT_SHORE || to == LEFT_SHORE)))
        return -2; // boat on wrong side
    if(count(from, type) < 1) return -3; // not enough people
    if(count(to, NOBODY) < 1) return -4; // no room
    
    return 1;
}

void World::move(Person type, Location from, Location to) {
    assert(is_legal_move(type, from, to) == 1);

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
}

bool World::boat_can_move() {
    return (count(BOAT, NOBODY) < BOAT_CAP);
}

void World::boat_move() {
    assert(boat_can_move());
    boat_side = (boat_side == LEFT_SIDE)?RIGHT_SIDE:LEFT_SIDE;
}

Person* World::field_addr(Location location) {
    switch (location) {
        case LEFT_SHORE:
            return left;
        case RIGHT_SHORE:
            return right;
        case BOAT:
            return boat;
    }
}

int World::field_len(Location location) {
    switch (location) {
        case LEFT_SHORE:
        case RIGHT_SHORE:
            return NUM_TOTAL;
        case BOAT:
            return BOAT_CAP;
    }
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    switch(person) {
        case MISSIONARY:
            os << 'M';
            break;
        case CANNIBAL:
            os << 'C';
            break;
        case NOBODY:
            os << '_';
            break;
    }
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const World& world) {
    os << "[_";
    for (int i=0; i<NUM_TOTAL; i++) os << world.left[i];
    os << (world.boat_side == LEFT_SIDE?"_,|":"_,    |");
    for (int i=0; i<BOAT_CAP; i++) os << world.boat[i];
    os << (world.boat_side == LEFT_SIDE?"|    ,_":"|,_");
    for (int i=0; i<NUM_TOTAL; i++) os << world.right[i];
    os << "_]";
    return os;
}