#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <object.h>
#include <place.h>
#include <types.h>

#define MAX_LIFE                50
#define DEFAULT_INITIATIVE      10

namespace lab3
{
class Place;        // Forward declaration
/**
     * @brief The Actor class
     * Abstract class representing all the possible actors in the game
     */
class Character
{
public:
    Character();
    Character(const std::string &name, const std::string &type, Place *place);
    virtual ~Character();

    virtual bool action() = 0;
    void fight(Character &character);
    bool go(const std::string &direction);
    virtual bool pick_up(lab3::Object &object);
    virtual bool drop(lab3::Object &object);
    void talk_to(Character* character);
    void set_place(Place* p);

    // Accessors
    int getLifePoints()             const;
    int getStrength()               const;
    int getDefense()                const;
    int getInitiative()             const;
    bool isAlive()                  const;

    Place *currentPlace();

    const std::vector<std::string> & getBasicCommands()     const;

    virtual std::string type()      const = 0;
    std::string name()              const;

    bool operator==(const Character &ch)    const;

protected:
    std::string name_;
    std::string type_;
    Place* current_place_;

    // ** Attributes
    int life_points_;
    int strength_;
    int defense_;
    int initiative_;

    std::vector<Object*> objects_;

    const std::vector<std::string> basic_commands_ =
    {
        "go",
        "fight",
        "talk to",
        "pick up",
        "drop",
        "exit game",
    };
};

}   // namespace lab3



#endif // CHARACTER_H
