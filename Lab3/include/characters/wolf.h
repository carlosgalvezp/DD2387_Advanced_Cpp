#ifndef WOLF_H
#define WOLF_H

#include <characters/animal.h>

#define WOLF_MAX_TEETH_SIZE      10
#define BLEED_HURT_POINTS        5

namespace lab3
{
namespace characters
{
class Wolf : public Animal
{
public:
    Wolf();
    Wolf(const std::string &name, Place *place);

    std::string action(bool display_info); // == 0
    ~Wolf();

private:
    int teeth_size_;    // The bigger, the more likely the bite works and the character bleeds forever.
                        // The teeth grow with age

    bool bleedingBite(Character& c);        //The character bleeds until it dies if it doesn't get cured
};
}
}
#endif // WOLF_H
