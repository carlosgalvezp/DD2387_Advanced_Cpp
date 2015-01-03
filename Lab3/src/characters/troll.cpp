#include <characters/troll.h>

using namespace lab3::characters;

Troll::Troll()
{}

Troll::Troll(const std::string &name)
    : Animal (name, TYPE_TROLL)
{}

Troll::~Troll()
{

}

