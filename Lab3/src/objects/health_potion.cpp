#include <objects/health_potion.h>

using namespace lab3::objects;

Health_Potion::Health_Potion()
{}

Health_Potion::Health_Potion(const std::string &name, int extra_points, int price, int weight, int volume)
    : Potion(name, "You recover some life points", extra_points, price, weight, volume)
{}

Health_Potion::~Health_Potion()
{}

bool Health_Potion::use(Character &c)
{
    c.add_life(this->extra_points_);
    std::stringstream ss;
    ss << "You have use a "<<this->name()<<", which gives you "<<extra_points_<<" life points. "<<
                 "Now you have "<<c.getLifePoints()<< " life points";
    lab3::utils_io::print_newline(ss.str());
    return true;
}
