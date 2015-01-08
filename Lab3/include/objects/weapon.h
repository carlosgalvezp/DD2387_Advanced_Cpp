#ifndef WEAPON_H
#define WEAPON_H

#include <object.h>

namespace lab3
{
namespace objects
{

class Weapon : Object
{
public:
    Weapon();

    int attackPoints()  const;

    ~Weapon();

protected:
    int attack_;
};

}
}
#endif // WEAPON_H
