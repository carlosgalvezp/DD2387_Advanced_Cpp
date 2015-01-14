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
    Weapon(const std::string &name,
           int hands_required,
           int attack_points,
           int price,
           int volume,
           int weight);

    int attackPoints()  const;

    ~Weapon();

protected:
    int attack_;
    int hands_required_; // If it's two hands, the player takes one more turn to attack
};

}
}
#endif // WEAPON_H
