#ifndef TROLL_H
#define TROLL_H

#include <characters/animal.h>

namespace lab3
{
namespace characters
{
class Troll : Animal
{
public:
    Troll();
    Troll(const std::string &name);
    ~Troll();
};

}
}

#endif // TROLL_H
