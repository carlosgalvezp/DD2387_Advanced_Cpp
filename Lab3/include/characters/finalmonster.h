#ifndef FINALMONSTER_H
#define FINALMONSTER_H

#include <character.h>
namespace lab3
{
namespace characters
{

class FinalMonster : public Character
{
public:
    FinalMonster();
    FinalMonster(const std::string &name, Place* place);
    ~FinalMonster();

    bool fight(Character &character);

    std::string action(bool display_info);
    std::string type() const;

private:
    bool defeated_player_;  // After the monster defeats the player, the wizard appears
    int distraction_;       // It gets easily distracted by the Princess. Therefore it is more likely to fail an attack
};

}
}

#endif // FINALMONSTER_H
