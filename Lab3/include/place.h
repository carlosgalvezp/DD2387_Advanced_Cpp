#ifndef PLACE_H
#define PLACE_H

// STL
#include <vector>
#include <string>

// Own classes
#include <object.h>
#include <character.h>

namespace lab3
{
/**
 * @brief The Place class
 * Class representing the possible places in which objects and items can be
 * in the game
 */
class Place
{
public:
    Place();

    std::vector<int> directions() const;
    Object& neighbour(int direction);

    std::string description() const;
    bool enter(Character &character);
    bool leave(Character &character);
    void pick_up(Object &object);
    void drop(Object &object);
};
} //namespace lab3


#endif // PLACE_H
