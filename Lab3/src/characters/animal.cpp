#include <characters/animal.h>

using namespace lab3::characters;

Animal::Animal()
{

}
Animal::Animal(const std::string &name, const std::string &type, Place* place)
    : Character(name,type, place)
{
    this->talk_msgs_ =
    {
        "Grrrr"
    };
}

Animal::~Animal()
{}

