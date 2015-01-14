#include <places/house.h>

using namespace lab3::places;

House::House(const std::string &name, bool is_open)
    : Indoor(name, is_open)
{}

bool House::enter(Character &character)
{
    return Indoor::enter(character);
}

House::~House()
{}

