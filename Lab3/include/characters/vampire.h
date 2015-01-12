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

    bool poison(Character &c);
    ~Vampire();

private:
    double poison_concentration_;    // The larger, the more likely it is to poison it's prey
};

}
}

#endif // TROLL_H
