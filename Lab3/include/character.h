#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <object.h>

namespace lab3
{
/**
     * @brief The Actor class
     * Abstract class representing all the possible actors in the game
     */
class Character
{
public:
    Character();

    std::string type()     const;
    std::string name()     const;

    void action();
    void go(int direction);
    void fight(Character &character);
    void pick_up(lab3::Object &object);
    void drop(lab3::Object &object);
    void talk_to(Character &character);
};

}   // namespace lab3



#endif // CHARACTER_H
