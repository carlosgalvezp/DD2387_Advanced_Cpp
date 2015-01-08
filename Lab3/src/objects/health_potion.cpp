#include <objects/health_potion.h>

using namespace lab3::objects;

Health_Potion::Health_Potion()
{}

Health_Potion::Health_Potion(const std::string &name, int extra_points, int price, int weight, int volume)
    : Potion(name, "You recover some life points", extra_points, price, weight, volume)
{}

Health_Potion::~Health_Potion()
{}
