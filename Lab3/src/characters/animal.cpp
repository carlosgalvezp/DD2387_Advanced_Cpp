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

    this->strength_ = PARAM_ANIMAL_STRENGTH;
    this->strength_ = PARAM_ANIMAL_DEFENSE;
}

Animal::~Animal()
{}

std::string Animal::action()
{
    lab3::utils_io::print_newline("[Animal::action] TO DO");
    return EVENT_NULL;
}
