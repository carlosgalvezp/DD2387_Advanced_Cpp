#ifndef FINALMONSTER_H
#define FINALMONSTER_H

#define DISTRACTION_MAX     0
#define DISTRACTION_MIN     50

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

    ActionResult fight(Character &character);
    ActionResult action(bool display_info);

    void addDistraction(int distraction);
    int getDistraction()    const;

    bool isEnemy(const Character &ch) const;

private:
    bool defeated_player_;  // After the monster defeats the player, the wizard appears
    int distraction_;       // It gets easily distracted by the Princess. Therefore it is more likely to fail an attack
};

}
}

#endif // FINALMONSTER_H
