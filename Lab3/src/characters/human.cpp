#include <characters/human.h>

using namespace lab3::characters;

Human::Human()
{}

Human::Human(const std::string &name, const std::string &type, Place *place)
    : Character(name, type, place)
{}

Human::~Human()
{

}

