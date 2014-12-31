#include <places/direction.h>

namespace lab3
{
Direction::Direction(const Movement &movement,
                          Place*   next_place)
    : movement_(movement), next_place_(next_place){}

}
