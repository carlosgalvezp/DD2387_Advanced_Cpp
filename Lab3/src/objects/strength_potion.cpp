#include <objects/strength_potion.h>

using namespace lab3::objects;

Strength_Potion::Strength_Potion(const std::string &name,
                                 int extra_points,
                                 int price,
                                 int weight,
                                 int volume)
    : Potion(name, "You gain strengh points", extra_points, price, weight, volume)
{}

Strength_Potion::~Strength_Potion()
{}

ActionResult Strength_Potion::use(Character &c)
{
    c.add_strength(this->extra_points_);
    return true;
}



