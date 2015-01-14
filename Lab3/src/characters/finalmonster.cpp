#include <characters/finalmonster.h>

using namespace lab3;
using namespace lab3::characters;

FinalMonster::FinalMonster(const std::string &name, Place *place)
    : Character(name, TYPE_FINAL_MONSTER, place),
      defeated_player_(false)
{
    this->talk_msgs_ = {"You will never get out of that jail dear Princess",
                        "Soon the entire city will be mine muahaha...",
                        "Your friends cannot defeat me!"};

}

FinalMonster::~FinalMonster()
{}

ActionResult FinalMonster::action(bool display_info)
{
    if(this->isFighting())
    {
        return fight(*this->fighter_);
    }
    else
    {
        return this->talk_to(*this->currentPlace()->getCharacter(NAME_PRINCESS));
    }
    return EVENT_NULL;
}

ActionResult FinalMonster::fight(Character &character)
{
    bool finished = Character::fight(character).success_;

    // Throw event when defeating the player for the first time
    if(finished && !defeated_player_ && character.name() == NAME_PLAYER)
    {
        defeated_player_ = true;
        return ActionResult(true,EVENT_TRIED_MONSTER);
    }
    return finished;
}

void FinalMonster::addDistraction(int distraction)
{
    this->distraction_ = std::max(std::min(this->distraction_ + distraction, DISTRACTION_MAX), DISTRACTION_MIN);
}

int FinalMonster::getDistraction()  const   {return this->distraction_; }
bool FinalMonster::isEnemy(const Character &ch) const   {  return true;}    // Everyone is an enemy
