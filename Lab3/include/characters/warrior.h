#ifndef WARRIOR_H
#define WARRIOR_H

#include <characters/human.h>

#define WARRIOR_TRAIN_INCREASE_SKILL    5
#define WARRIOR_INITIAL_SKILL           1
#define TRAIN_PROB           0.6

namespace lab3
{
namespace characters
{

class Warrior : public Human
{
public:
    Warrior(const std::string &name, Place* place);
    ~Warrior();

    ActionResult action(bool display_info); // = 0;

    int getSkillPoints()    const;

    int getStrength()   const;
    int getDefense()    const;

private:
    int skill_; // The more the skill, the more the final strength and defense

    Character *lookForAnimals()   const;
    ActionResult train();
};

}
}

#endif // WARRIOR_H
