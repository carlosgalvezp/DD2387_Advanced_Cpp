#ifndef ANIMAL_H
#define ANIMAL_H

#include <character.h>

#define PARAM_ANIMAL_STRENGTH   10
#define PARAM_ANIMAL_DEFENSE    5

namespace lab3
{
namespace characters
{

class Animal : public Character
{
public:
    Animal();
    Animal(const std::string &name, const std::string &type, Place *place);

    std::string action(bool display_info);
    bool lookForFood();                     // Gives life points
    ~Animal();

protected:
    Place *natural_habitat_;        // If the animal is not here, its chances to find food are smaller
    int age_;                   // Animals get old and therefore fight worse. Eventually they die
};

}
}

#endif // ANIMAL_H
