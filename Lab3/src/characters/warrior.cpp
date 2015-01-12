#include <characters/warrior.h>

using namespace lab3::characters;

Warrior::Warrior()
{}

Warrior::Warrior(const std::string &name, Place *place)
    :Human(name, TYPE_HUMAN, place)
{
    this->talk_msgs_ =
    {
        "Hi, I am a Warrior. I am here to protect the city from the animals and monster that might"
        " come and try to hurt our people"
    };
}

Warrior::~Warrior()
{}

