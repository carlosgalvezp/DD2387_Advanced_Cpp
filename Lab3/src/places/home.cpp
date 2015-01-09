#include <places/home.h>

using namespace lab3::places;

Home::Home()
{}

Home::Home(const std::string &name)
    : House(name, true)
{}

void Home::rest(Character &c) const
{
    c.add_life(MAX_LIFE/2.0);
}

Home::~Home()
{}

