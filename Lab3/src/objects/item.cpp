#include <objects/item.h>

using namespace lab3::objects;

Item::Item()
{}

Item::Item(const std::string &name, int price, int weight, int volume)
    : Object(name, price, weight, volume)
{}

Item::~Item()
{}

