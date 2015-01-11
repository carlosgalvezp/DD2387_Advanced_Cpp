#ifndef PLACE_H
#define PLACE_H

// STL
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <utility>
#include <iostream>
#include <string>
#include <sstream>

// Own classes
#include <object.h>
#include <character.h>
#include <utils/utils_io.h>

namespace lab3
{
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

    Place& neighbour(const std::string &direction);

    virtual bool enter(Character &character);
    virtual bool leave(Character &character);
    virtual bool pick_up(Object &object);
    virtual void drop(Object &object);

    void addDirection(const std::string &d, Place* p);
    virtual void generateObjects();

    void killCharacter(Character &character);

    void addCharacter(Character &character);
    void addObject(Object &o);

    // Accessors
    std::string name()        const;
    std::string description() const;
    const std::map<std::string, Place*>& directions() const;
    const std::vector<Object*> &objects()             const;
    const std::vector<Character*> &characters()       const;

    virtual const std::vector<std::string> &getCommands()   const;

    bool operator==(const Place& p) const;
protected:
    std::string name_;

    std::vector<Object*> objects_;
    std::vector<Character*> characters_;
    std::map<std::string, Place*> directions_;

    void display_information(const Character &character);

    std::vector<std::string> place_commands_;
};

namespace places
{
    void connectPlaces(Place &p1, Place &p2, const std::string &d12);
}

} //namespace lab3


#endif // PLACE_H
