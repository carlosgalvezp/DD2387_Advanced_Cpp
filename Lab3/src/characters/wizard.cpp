#include <characters/wizard.h>

using namespace lab3::characters;

Wizard::Wizard(const std::string &name, Place *place, std::map<std::string, Place *> &world_places)
    : Character(name, TYPE_WIZARD, place),
      talked_to_player_(false),
      world_places_(world_places)
{
    this->talk_msgs_ = {"I am the "+name+". I only appear in crucial moments, and only the right person can see me "
                        "The Princess needs to be saved, for which the monster inside the King's Castle needs to be killed... "
                        "However, there is no weapon in the world that can break through its thick skin. Some magic is needed "
                        "in order to weaken it. I will come with you and together we will destroy the monster"};
}

std::string Wizard::action(bool display_info)
{
    std::cout << "[Wizard::action] TO DO" << std::endl;
    return EVENT_NULL;
}

void Wizard::talk_to(Character &character)
{
    Character::talk_to(character);

    if(character.type() == TYPE_PLAYER && this->currentPlace()->name() != NAME_CASTLE) // The wizard will be moved to the Castle
    {
        this->teleport(NAME_CASTLE);
    }
}

bool Wizard::teleport(const std::string &place)
{
    try
    {
        this->world_places_.at(place)->enter(*this);
        return true;
    }
    catch(std::exception &e){}
    return false;
}

Wizard::~Wizard()
{}

