#ifndef PLAYER_H
#define PLAYER_H

#include <characters/human.h>
#include <utils/utils_io.h>
#include <utils/input.h>
#include <objects/container.h>

#include <game_engine.h>

// STL
#include <utility>

#define DEFAULT_BACKPACK_VOLUME 50
#define DEFAULT_BACKPACK_WEIGHT  1
#define DEFAULT_BACKPACK_MAX_VOLUME 50
#define DEFAULT_BACKPACK_MAX_WEIGHT 20

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

    bool action();
    bool pick_up(Object &object);
    bool drop(Object &object);
    void talk_to(Character* character);
    bool fight(Character &character);

    void status()                   const;
    std::string type()              const;
    bool finishedGame()             const;

    std::vector<std::string> getCommands();

private:
    bool finished_game_;
};

}
}



#endif // PLAYER_H
