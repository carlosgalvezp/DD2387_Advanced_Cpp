#ifndef PALADIN_H
#define PALADIN_H

#include <character.h>

namespace lab3
{
namespace characters
{

class Paladin : public Character
{
public:
    Paladin();
    ~Paladin();

    std::string type() const;
};

}
}

#endif // PALADIN_H
