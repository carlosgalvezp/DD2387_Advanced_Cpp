#include <objects/potion.h>

using namespace lab3::objects;

Potion::Potion()
{}

Potion::Potion(const std::string &name,
               const std::string &description,
               int extra_points,
               int price,
               int volume,
               int weight)
    : Item(name, description, price, weight, volume),
      extra_points_(extra_points)
{}

Potion::~Potion()
{}


