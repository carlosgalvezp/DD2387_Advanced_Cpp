#ifndef WOLF_H
#define WOLF_H

#include <characters/animal.h>

#define WOLF_MAX_TEETH_SIZE      10
#define BLEED_HURT_POINTS        20
#define BLEED_HURT_PROB          0.3

#define WOLF_REPRODUCTION_FREQUENCY     10 // in days

namespace lab3
{
namespace characters
{
class Wolf : public Animal
{
public:
    Wolf(Place *place, Place *natural_habitat);
    ~Wolf();

    ActionResult action(bool display_info);

    Character* reproduce();

private:
    int teeth_size_;    // The bigger, the more likely the bite works and the character bleeds forever.
                        // The teeth grow with age

    static int id_;

    bool isEnemy(const Character &ch) const;
    bool bleedingBite(Character& c);        //The character bleeds until it dies if it doesn't get cured
};
}
}
#endif // WOLF_H
