#include <objects/item.h>

using namespace lab3::objects;

Item::Item()
{}

Item::Item(const std::string &name,
           const std::string &description,
           int price,
           int weight,
           int volume)
    : Object(name, description, price, weight, volume)
{}

Item::~Item()
{}

