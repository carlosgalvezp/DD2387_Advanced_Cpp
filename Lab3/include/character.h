#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <object.h>
#include <places/direction.h>

namespace lab3
{
class Direction;
/**
     * @brief The Actor class
     * Abstract class representing all the possible actors in the game
     */
class Character
{
public:
    Character();
    Character(const std::string &name);
    virtual ~Character();

    void action();
    void go(Direction * direction);
    void fight(Character &character);
    void pick_up(lab3::Object &object);
    void drop(lab3::Object &object);
    void talk_to(Character &character);

    // Accessors
    int getLifePoints()             const;
    int getStrength()               const;
    virtual std::string type()      const = 0;
    std::string name()              const;

protected:
    int life_points_;
    int strength_;
    std::string name_;
    std::string type_;

};

}   // namespace lab3



#endif // CHARACTER_H
