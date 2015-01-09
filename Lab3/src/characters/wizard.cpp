#include <characters/wizard.h>

using namespace lab3::characters;

Wizard::Wizard()
{}

Wizard::Wizard(const std::string &name, Place *place)
    : Character(name, TYPE_WIZARD, place)
{
    this->talk_msgs_ = {"I am the "+name+". I only appear in crucial moments, and only the right person can see me"
                        "The Princess needs to be saved, for which the monster inside the King's Castle needs to be killed..."
                        "However, there is no weapon in the world that can break through its thick skin. Some magic is needed "
                        "in order to weaken it. I will come with you and together we will destroy the monster"};
}

std::string Wizard::action(bool display_info)
{
    std::cout << "[Wizard::action] TO DO" << std::endl;
    return EVENT_NULL;
}

Wizard::~Wizard()
{}

