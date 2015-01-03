#include <characters/human.h>

using namespace lab3::characters;

Human::Human()
{}

Human::Human(const std::string &name, const std::string &type)
    : Character(name, type)
{}

Human::~Human()
{

}

