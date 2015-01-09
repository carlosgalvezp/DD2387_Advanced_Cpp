#ifndef WEAPON_H
#define WEAPON_H

#include <objects/equipment.h>

namespace lab3
{
namespace objects
{

class Weapon : public Equipment
{
public:
    Weapon();
    Weapon(const std::string &name,
           int attack_points,
           int hands_required,
           int price,
           int volume,
           int weight);

    int attackPoints()  const;

    ~Weapon();

protected:
    int attack_;
    int hands_required_;
};

}
}
#endif // WEAPON_H
