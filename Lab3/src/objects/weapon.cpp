#include <objects/weapon.h>

using namespace lab3::objects;

Weapon::Weapon()
{}

Weapon::Weapon(const std::string &name,
               int attack_points,
               int hands_required,
               int price,
               int volume,
               int weight)
    : Object(name, "A weapon that gives you extra strength", price, volume, weight),
      attack_(attack_points),
      hands_required_(hands_required)
{}


Weapon::~Weapon()
{}

int Weapon::attackPoints() const {return this->attack_;}

