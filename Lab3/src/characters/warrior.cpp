#include <characters/warrior.h>

using namespace lab3::characters;
using namespace lab3;

Warrior::Warrior()
{}

Warrior::Warrior(const std::string &name, Place *place)
    :Human(name, TYPE_HUMAN, place), skill_(WARRIOR_INITIAL_SKILL)
{
    this->talk_msgs_ =
    {
        "Hi, I am a Warrior. I am here to protect the city from the animals and monsters that might"
        " come and try to hurt our people"
    };
}

Warrior::~Warrior()
{}

int Warrior::getStrength()  const
{
    return Character::getStrength() + this->skill_;
}

int Warrior::getDefense()   const
{
    return Character::getDefense() + this->skill_;
}

std::string Warrior::action(bool display_info)
{
    Character*c = lookForEnemies();
    if(c != nullptr)            // ** Fight to animals if they appear in the place
    {
        this->fight(*c);
    }
    else                        // ** Else train or talk with P =
    {
        // Maybe talk to player, if it's there
        Character* player = this->currentPlace()->getCharacter(NAME_PLAYER);
        if(player != nullptr && lab3::utils::eventHappens(1-TRAIN_PROB))
        {
            this->talk_to(*player);
        }
        else
        {
            this->train();
        }
    }
    return EVENT_NULL;
}

void Warrior::train()
{
    this->skill_ = std::min(this->skill_ + WARRIOR_TRAIN_INCREASE_SKILL, MAX_STRENGTH);
    std::stringstream ss;
    ss << this->name()<<" trains to gain experience. Now his skill level is "<<this->skill_<<" points";
    lab3::utils_io::print_newline(ss.str());
}

int Warrior::getSkillPoints()   const   {return this->skill_;}
