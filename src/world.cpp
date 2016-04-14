#include "world.h"
#include <iostream>
#include <assert.h>

// Default constructor
World::World(int m_left, int c_left, int m_right, int c_right, Side boat_side) {
    // Set metadata
    num_m = m_left + m_right;
    num_c = c_left + c_right;
    this->boat_side = boat_side;
    
    // allocate locations
    left = new Person[num_m+num_c];
    right = new Person[num_m+num_c];
    boat = new Person[BOAT_CAP];
    
    // populate
    for(int i=0; i<num_m+num_c; i++) {
        if(i<m_left+c_left) {
            left[i] = (i<m_left)?MISSIONARY:CANNIBAL;
        } else {
            left[i] = NOBODY;
        }
        
        if(i<m_right+c_right) {
            right[i] = (i<m_right)?MISSIONARY:CANNIBAL;
        } else {
            right[i] = NOBODY;
        }
    }

    for(int i=0; i<BOAT_CAP; i++)
        boat[i] = NOBODY;
}

// Copy constructor
World::World(const World& w) {
    // Set metadata
    num_m = w.num_m;
    num_c = w.num_c;
    boat_side = w.boat_side;
    
    // allocate locations
    left = new Person[num_m+num_c];
    right = new Person[num_m+num_c];
    boat = new Person[BOAT_CAP];
    
    // copy values
    for(int i=0; i<num_m+num_c; i++) {
        left[i] = w.left[i];
        right[i] = w.right[i];
    }
    
    for(int i=0; i<BOAT_CAP; i++)
        boat[i] = w.boat[i];
}

// Destructor
World::~World() {
    delete left;
    delete right;
    delete boat;
}

int World::count(Location location, Person type) const {
    Person * set = field_addr(location);
    int count = field_len(location);
    int sum = 0;

    for (int i=0; i<count; i++)
        if (set[i] == type)
            sum++;

    return sum;
}

int World::count(Side side, Person type) const {
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
bool World::is_legal_move(Person type, Location from, Location to) const {
    if((from != BOAT && to != BOAT) || from == to) return false; // Must include boat
    if(((boat_side == LEFT_SIDE) && (from == RIGHT_SHORE || to == RIGHT_SHORE)) || \
       ((boat_side == RIGHT_SIDE) && (from == LEFT_SHORE || to == LEFT_SHORE)))
        return false; // boat on wrong side
    if(count(from, type) < 1) return false; // not enough people
    if(count(to, NOBODY) < 1) return false; // no room
    
    return true;
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

bool World::boat_can_move() const {
    return (count(BOAT, NOBODY) < BOAT_CAP);
}

void World::boat_move() {
    assert(boat_can_move());
    boat_side = (boat_side == LEFT_SIDE)?RIGHT_SIDE:LEFT_SIDE;
}

bool World::fail() const {
    return (count(LEFT_SIDE, CANNIBAL)  > count(LEFT_SIDE, MISSIONARY) ||
            count(RIGHT_SIDE, CANNIBAL) > count(RIGHT_SIDE, MISSIONARY));
}

Person* World::field_addr(Location location) const {
    switch (location) {
        case LEFT_SHORE:
            return left;
        case RIGHT_SHORE:
            return right;
        case BOAT:
            return boat;
    }
}

int World::field_len(Location location) const {
    switch (location) {
        case LEFT_SHORE:
        case RIGHT_SHORE:
            return num_m+num_c;
        case BOAT:
            return BOAT_CAP;
    }
}

bool World::operator==(const World& w) const {
    return ( // Right shore not included for efficiency; mathematically irrelevant
        (count(LEFT_SHORE, MISSIONARY) == w.count(LEFT_SHORE, MISSIONARY))  &&
        (count(BOAT, MISSIONARY)       == w.count(BOAT, MISSIONARY))        &&
        
        (count(LEFT_SHORE, CANNIBAL)   == w.count(LEFT_SHORE, CANNIBAL))    &&
        (count(BOAT, CANNIBAL)         == w.count(BOAT, CANNIBAL))
    );
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
    for (int i=0; i<world.num_m+world.num_c; i++) os << world.left[i];
    os << (world.boat_side == LEFT_SIDE?"_,|":"_,    |");
    for (int i=0; i<BOAT_CAP; i++) os << world.boat[i];
    os << (world.boat_side == LEFT_SIDE?"|    ,_":"|,_");
    for (int i=0; i<world.num_m+world.num_c; i++) os << world.right[i];
    os << "_]";
    return os;
}