#ifndef CHARACTER_H
#define CHARACTER_H

// STL
#include <string>

#include <object.h>
#include <place.h>
#include <types.h>
#include <utils/utils_io.h>
#include <events_def.h>

#define MAX_LIFE                50
#define MAX_STRENGTH            50
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

    virtual std::string action() = 0;
    virtual bool fight(Character &character);
    bool go(const std::string &direction);
    virtual bool pick_up(lab3::Object &object);
    virtual bool drop(lab3::Object &object);
    virtual void talk_to(Character* character);

    // Setters
    void set_place(Place* p);
    void set_fighting(bool fighting);
    void set_damage(int damage);
    void add_life(int life);
    void add_strength(int stregth);

    // Accessors
    int getLifePoints()             const;
    int getStrength()               const;
    int getDefense()                const;
    int getInitiative()             const;
    bool isAlive()                  const;
    bool isFighting()               const;

    const Place* currentPlace()      const;
    Place*       currentPlace()      ;


    const    std::vector<Object*>& objects()    const;
             std::vector<Object*>& objects();

    const std::vector<std::string> & getBasicCommands()     const;
    virtual std::vector<std::string>  getCommands()         const;

    const std::vector<std::string> & getTalkMessages()      const;

    std::string type()              const;
    std::string name()              const;

    bool operator==(const Character &ch)    const;
    bool operator!=(const Character &ch)    const;

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

    bool is_fighting_;

    std::vector<std::string> talk_msgs_;

    const std::vector<std::string> fight_basic_commands_ =
    {
        "attack",
        "scape"
    };

    const std::vector<std::string> basic_commands_ =
    {
        "go",
        "fight",
        "talk to",
        "pick up",
        "drop",
        "exit game",
    };

    // ** Actual commands, that each character will extend
    std::vector<std::string> commands_ = basic_commands_;
    std::vector<std::string> fight_commands_ = fight_basic_commands_;
};

int computeDamage(const Character &attacker, const Character &defender);
}   // namespace lab3



#endif // CHARACTER_H
