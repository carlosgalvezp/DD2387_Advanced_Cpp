#ifndef DIRECTION_H
#define DIRECTION_H

#include <place.h>
namespace lab3
{

class Place;

enum Movement
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

struct Direction
{
    Direction(const Movement &movement,
                    Place*   next_place);
    Movement movement_;
    Place*   next_place_;
};

}

#endif // DIRECTION_H
