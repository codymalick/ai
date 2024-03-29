#ifndef _WORLD
#define _WORLD

#define BOAT_CAP 2
#include <iostream>

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
        World(int, int, int, int, Side);
        World(const World&);
        ~World();
        
        int count(Side, Person) const;
        int count(Location, Person) const;
        Person boat_at(int);
        bool is_legal_move(Person, Location, Location) const;
        void move(Person, Location, Location);
        inline Side get_boat_side() const { return boat_side; }
        inline Location boat_closest() const { return (boat_side == LEFT_SIDE)?LEFT_SHORE:RIGHT_SHORE; }
        bool boat_can_move() const;
        void boat_move();
        bool fail() const;
        int heuristance(const World&);
        
        bool operator==(const World&) const;
        friend std::ostream& operator<<(std::ostream&, const World&);
        
    private:
        int num_m;
        int num_c;
        Person *left;
        Person *right;
        Person *boat;
        Side boat_side;
        
        
        Person* field_addr(Location) const;
        int field_len(Location) const;
};

#endif