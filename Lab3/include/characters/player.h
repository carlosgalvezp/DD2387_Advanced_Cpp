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
    std::string type() const;

private:
    bool rescued_princess;
};

}
}



#endif // PLAYER_H
