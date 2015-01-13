#ifndef VAMPIRE_H
#define VAMPIRE_H

#include <characters/animal.h>
#include <characters/troll.h>

#define POISON_REDUCE_TRY       0.4     // If it tries to poison, the value is reduced by this amount afterwards
#define POISON_INCREASE_RATE    0.2     // The poison concentration increases by this amount after every turn

#define POISON_PROB             0.2
#define POISON_HURT_POINTS      5       // The poisoned character loses this amount every turn it's poisoned

namespace lab3
{
namespace characters
{
class Vampire : Animal
{
public:
    Vampire();
    Vampire(const std::string &name, Place* place, Place* natural_habitat);

    std::string action(bool display_info); //  = 0;

    double getPoisonConcentration() const;

    ~Vampire();

private:
    double poison_concentration_;    // The larger, the more likely it is to poison it's prey


    bool poison(Character &c);
    bool isEnemy(const Character &ch) const;
};

}
}

#endif // TROLL_H
