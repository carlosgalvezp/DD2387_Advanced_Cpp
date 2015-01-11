#ifndef PLAYER_H
#define PLAYER_H

#include <characters/human.h>
#include <utils/utils_io.h>
#include <utils/input.h>
#include <objects/container.h>
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

    std::string action(bool display_info);
    bool pick_up(Object &object);
    bool drop(Object &object);
    void talk_to(Character* character);
    bool fight(Character &character);

    void status()                   const;
    std::string type()              const;
    bool finishedGame()             const;

    std::vector<std::string> getCommands();

    objects::Container *getBackpack();

    bool use(Object &o);
private:
    bool finished_game_;
    int experience_;
    int kills_wolf_;
    int kills_vampire_;
    bool event_trained_;
    Place* home_;

    void check_event_trained(const Character &character);
    void check_event_final_monster(const Character &character);
};

}
}



#endif // PLAYER_H
