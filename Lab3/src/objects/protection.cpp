#include <objects/protection.h>

using namespace lab3::objects;

Protection::Protection(const std::string &name,
                       int defense_points,
                       int price,
                       int volume,
                       int weight)
    : Equipment(name, "A protection that gives you extra defense", price, volume, weight), defense_(defense_points)
{}

Protection::~Protection()
{}

int Protection::defensePoints() const   {return this->defense_;}


