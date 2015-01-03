#include <characters/wolf.h>

using namespace lab3::characters;

Wolf::Wolf()
{}

Wolf::Wolf(const std::string &name, Place *place)
    : Animal(name, TYPE_WOLF, place)
{}

Wolf::~Wolf()
{

}

