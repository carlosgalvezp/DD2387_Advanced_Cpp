#ifndef CHARACTER_H
#define CHARACTER_H

// STL
#include <string>

#include <object.h>
#include <place.h>
#include <utils/utils_io.h>
#include <utils/utils.h>
#include <names.h>

#include <actionresult.h>

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
    Character(const std::string &name, const std::string &type, Place *place);
    virtual ~Character();

    // Base functions
    virtual ActionResult action(bool display_info) = 0;
    virtual ActionResult fight(Character &character);
    virtual ActionResult scape();

    virtual ActionResult go(const std::string &direction);
    virtual ActionResult pick_up(lab3::Object &object);
    virtual ActionResult drop(lab3::Object &object);
    virtual ActionResult talk_to(Character& character);

    // Setters
    void set_place(Place* p);
    void set_fighting(bool fighting);
    void set_damage(int damage);
    void add_life(int life);
    void set_life(int life);
    void add_strength(int stregth);
    void add_defense(int defense);
    void set_talk_msgs(const std::vector<std::string> &msgs);
    void set_constantly_damaged(const std::string& type, int points);
    void remove_constantly_damaged();

    void applyConstantDamage();
    void endFight();


    // Accessors
    const std::string& type()                      const;
    const std::string& name()                      const;
    int getLifePoints()                     const;
    virtual int getStrength()               const;
    virtual int getDefense()                const;
    virtual int getInitiative()             const;
    bool isAlive()                          const;
    bool isFighting()                       const;

    const Place* currentPlace()             const;  // Read-only
    Place*       currentPlace();

    const Character* fighter()              const;
          Character* fighter();


    const    std::vector<Object*>& objects()    const;
             std::vector<Object*>& objects();

    virtual const std::vector<std::string> &getCommands()         const;
            const std::vector<std::string> &getTalkMessages()     const;


    bool isConstantlyDamaged()                      const;

    bool operator==(const Character &ch)            const;
    bool operator!=(const Character &ch)            const;

    virtual bool isEnemy(const Character &ch)       const = 0;
    virtual Character* lookForEnemies()             const;
protected:
    std::string name_;
    std::string type_;
    Place* current_place_;  // Not using reference since it cannot be changed afterwards!!

    // ** Attributes
    int life_points_;
    int strength_;
    int defense_;
    int initiative_;

    bool is_fighting_;
    int n_msg_talk_;

    int constant_damage_points_;
    std::string constant_damage_type_;

    std::vector<Object*> objects_;
    std::vector<std::string> talk_msgs_;
    std::vector<std::string> action_commands_;

    Character* fighter_;
};

int computeDamage(const Character &attacker, const Character &defender);
}   // namespace lab3



#endif // CHARACTER_H
