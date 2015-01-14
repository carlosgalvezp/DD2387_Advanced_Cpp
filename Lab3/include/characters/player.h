#ifndef PLAYER_H
#define PLAYER_H

#include <characters/human.h>
#include <utils/utils_io.h>
#include <utils/input.h>
#include <objects/container.h>
#include <objects/weapon.h>
#include <objects/protection.h>

#include <objects/usable.h>

#include <characters/wolf.h>
#include <characters/vampire.h>

#include <game_engine.h>

// STL
#include <utility>

#define DEFAULT_BACKPACK_VOLUME 50
#define DEFAULT_BACKPACK_WEIGHT  1
#define DEFAULT_BACKPACK_MAX_VOLUME 10
#define DEFAULT_BACKPACK_MAX_WEIGHT 10

#define MIN_EXPERIENCE 2
#define MIN_KILL_ANIMAL 1

#define INITIAL_MONEY   50

namespace lab3
{
namespace characters
{

class Player : public Human
{
public:

    Player();
    Player(const std::string &name, Place *place);
    ~Player();

    ActionResult action(bool display_info);
    ActionResult pick_up(Object &object);
    ActionResult drop(Object &object);
    ActionResult talk_to(Character* character);
    ActionResult fight(Character &character);

    void status()                   const;
    std::string type()              const;
    bool finishedGame()             const;

    std::vector<std::string> getCommands();

    objects::Container      *getBackpack();
    objects::Weapon         *getWeapon()            const;
    objects::Protection     *getProtection()        const;

    ActionResult use(Object &o);

    int getStrength()   const;
    int getDefense()    const;
private:
    bool finished_game_;
    int experience_;
    int kills_wolf_;
    int kills_vampire_;
    bool event_trained_;
    Place* home_;

    ActionResult check_event_trained(const Character &character);
    ActionResult check_event_final_monster(const Character &character);

    ActionResult pick_up_backpack(objects::Container &new_backpack);
};

}
}



#endif // PLAYER_H
