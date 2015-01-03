#include <characters/troll.h>

using namespace lab3::characters;

Troll::Troll()
{}

Troll::Troll(const std::string &name, Place* place)
    : Animal (name, TYPE_TROLL, place)
{}

Troll::~Troll()
{

}

