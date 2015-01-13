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

std::string Warrior::action(bool display_info)
{
    std::cout << "[Warrior::action]"<<std::endl;
    return EVENT_NULL;
}

void Warrior::train()
{
    this->skill_ = std::min(this->skill_ + WARRIOR_TRAIN_INCREASE_SKILL, MAX_STRENGTH);
    std::stringstream ss;
    ss << "The warrior "<<this->name()<<" trains to gain experience. Now his skill level is "<<this->skill_<<" points";
    lab3::utils_io::print_newline(ss.str());
}

int Warrior::getSkillPoints()   const   {return this->skill_;}
