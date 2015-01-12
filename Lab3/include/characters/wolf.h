#ifndef WOLF_H
#define WOLF_H

#include <characters/animal.h>

namespace lab3
{
namespace characters
{
class Wolf : public Animal
{
public:
    Wolf();
    Wolf(const std::string &name, Place *place);

    std::string type() const;
    bool bleedingBite(Character& c);        //The character bleeds until it dies if it doesn't get cured
    ~Wolf();

private:
    int teeth_size_;    // The bigger, the more likely the bite works and the character bleeds forever.
                        // The teeth grow with age
};
}
}
#endif // WOLF_H
