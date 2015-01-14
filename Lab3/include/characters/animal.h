#ifndef ANIMAL_H
#define ANIMAL_H

#include <character.h>

#define PROB_FOOD_IN        0.8
#define PROB_FOOD_OUT       0.3

#define LIFE_FOOD           5

namespace lab3
{
namespace characters
{

class Animal : public Character
{
public:
    Animal();
    Animal(const std::string &name, const std::string &type, Place *place, Place *natural_habitat);

    ActionResult action(bool display_info)=0;
    ~Animal();

protected:
    Place *natural_habitat_;        // If the animal is not here, its chances to find food are smaller
    int age_;                       // Animals get old and therefore fight worse. Eventually they die

    bool lookForFood();               // Gives life points
};

}
}

#endif // ANIMAL_H
