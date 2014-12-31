#ifndef PLACE_H
#define PLACE_H

// STL
#include <vector>
#include <string>
#include <algorithm>

// Own classes
#include <object.h>
#include <character.h>
#include <places/direction.h>
namespace lab3
{
struct Direction;
class Character;
/**
 * @brief The Place class
 * Class representing the possible places in which objects and items can be
 * in the game
 */
class Place
{
public:
    Place();
    Place(const std::string &name);
    virtual ~Place();

    Place& neighbour(int direction);

    bool enter(Character &character);
    bool leave(Character &character);
    bool pick_up(Object &object);
    void drop(Object &object);

    void addDirection(Direction *direction);

    // Accessors
    std::string description() const;
    const std::vector<Direction*>& directions() const;

private:
    std::string name_;
    std::string description_;

    std::vector<Object*> objects_;
    std::vector<Character*> characters_;
    std::vector<Direction*> directions_;
};

} //namespace lab3


#endif // PLACE_H
