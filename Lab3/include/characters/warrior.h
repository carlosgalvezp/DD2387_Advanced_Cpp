#ifndef WARRIOR_H
#define WARRIOR_H

#include <characters/human.h>

#define WARRIOR_TRAIN_INCREASE_SKILL    5

namespace lab3
{
namespace characters
{

class Warrior : public Human
{
public:
    Warrior();
    Warrior(const std::string &name, Place* place);
    ~Warrior();

    std::string action(bool display_info); // = 0;

    int getSkillPoints()    const;

private:
    int skill_; // The more the skill, the more the final strength and defense

    void train();
};

}
}

#endif // WARRIOR_H
