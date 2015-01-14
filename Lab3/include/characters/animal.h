#ifndef ANIMAL_H
#define ANIMAL_H

#include <character.h>

#define PROB_FOOD_IN        0.5
#define PROB_FOOD_OUT       0.2

#define LIFE_FOOD           2

namespace lab3
{
namespace characters
{

class Animal : public Character
{
public:
    Animal(const std::string &name, const std::string &type, Place *place, Place *natural_habitat, int reproduction_frequency);

    ActionResult action(bool display_info)=0;

    virtual Character* reproduce() = 0; // Non-const since it modifies internal counters
    ~Animal();

protected:
    Place *natural_habitat_;        // If the animal is not here, its chances to find food are smaller
    int age_;                       // Animals get old and therefore fight worse. Eventually they die

    double p_food_, p_go_, p_fight_;
    int reproduction_frequency_;
    int days_since_last_reproduced_;

    bool lookForFood();               // Gives life points
};

}
}

#endif // ANIMAL_H
