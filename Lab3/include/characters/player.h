#ifndef PLAYER_H
#define PLAYER_H

#include <characters/human.h>
#include <utils/utils_io.h>
#include <utils/input.h>


namespace lab3
{
namespace characters
{

class Player : public Human
{
public:
    Player();
    Player(const std::string &name);
    ~Player();

    bool action();
    std::string type() const;

private:
    bool rescued_princess;
};

}
}



#endif // PLAYER_H
