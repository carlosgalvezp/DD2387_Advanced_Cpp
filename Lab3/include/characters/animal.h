#ifndef ANIMAL_H
#define ANIMAL_H

#include <character.h>

namespace lab3
{
namespace characters
{

class Animal : public Character
{
public:
    Animal();
    Animal(const std::string &name, const std::string &type);
    ~Animal();
};

}
}

#endif // ANIMAL_H
