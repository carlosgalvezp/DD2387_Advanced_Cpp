#include <characters/troll.h>

using namespace lab3::characters;
using namespace lab3;

Troll::Troll()
{}

Troll::Troll(const std::string &name, Place *place)
    : Animal(name, TYPE_TROLL, place)
{}

Troll::~Troll()
{}

std::string Troll::action(bool display_info)
{
    std::cout << "[Troll::action]"<<std::endl;
    return EVENT_NULL;
}

bool Troll::isEnemy(const Character &ch) const
{
    return ch.type() != TYPE_TROLL;
}
