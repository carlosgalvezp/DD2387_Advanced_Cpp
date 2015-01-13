#ifndef TROLL_H
#define TROLL_H

#include <characters/animal.h>

#define TIREDNESS_MAX  10
#define TIREDNESS_STEP 1

namespace lab3
{
namespace characters
{

class Troll : public Animal
{
public:
    Troll();
    Troll(const std::string &name, Place *place, Place* natural_habitat);

    std::string action(bool display_info); // == 0

    bool fight(Character &character);
    ~Troll();

private:
    int tiredness_;  // Trolls are likely to fall asleep if they are tired
    bool isEnemy(const Character &ch) const;
    void sleep();
};

}
}

#endif // TROLL_H
