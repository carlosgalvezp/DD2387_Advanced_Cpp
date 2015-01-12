#ifndef WARRIOR_H
#define WARRIOR_H

#include <characters/human.h>

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

    void train();

private:
    int skill_; // The more the skill, the more the final strength and defense
};

}
}

#endif // WARRIOR_H
