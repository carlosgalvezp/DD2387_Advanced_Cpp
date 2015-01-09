#ifndef VAMPIRE_H
#define VAMPIRE_H

#include <characters/animal.h>

namespace lab3
{
namespace characters
{
class Vampire : Animal
{
public:
    Vampire();
    Vampire(const std::string &name, Place *place);
    ~Vampire();
};

}
}

#endif // TROLL_H
