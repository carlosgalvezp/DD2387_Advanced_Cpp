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

    std::string action();
    ~Animal();
};

}
}

#endif // ANIMAL_H
