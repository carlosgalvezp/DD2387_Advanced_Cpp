#include <characters/finalmonster.h>

using namespace lab3;
using namespace lab3::characters;

FinalMonster::FinalMonster()
{}

FinalMonster::FinalMonster(const std::string &name, Place *place)
    : Character(name, TYPE_FINAL_MONSTER, place),
      defeated_player_(false)
{}

FinalMonster::~FinalMonster()
{}

std::string FinalMonster::action(bool display_info)
{

    if(this->isFighting())
    {
        try
        {
            fight(*this->fighter_);
        }
        catch(std::runtime_error &e)
        {
            return e.what();
        }
    }
    return EVENT_NULL;
}

std::string FinalMonster::type() const
{
    return TYPE_FINAL_MONSTER;
}

bool FinalMonster::fight(Character &character)
{
    bool finished = Character::fight(character);

    // Throw event when defeating the player for the first time
    if(finished && !defeated_player_ && character.type() == TYPE_PLAYER)
    {
        defeated_player_ = true;
        throw std::runtime_error(EVENT_TRIED_MONSTER);
    }
    return finished;
}
