#include <characters/wolf.h>

using namespace lab3::characters;

Wolf::Wolf()
{}

Wolf::Wolf(const std::string &name)
    : Animal(name, TYPE_WOLF)
{}

Wolf::~Wolf()
{

}

