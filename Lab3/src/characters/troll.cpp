#include <characters/troll.h>

using namespace lab3::characters;
using namespace lab3;

Troll::Troll()
{}

Troll::Troll(const std::string &name, Place *place, Place *natural_habitat)
    : Animal(name, TYPE_TROLL, place, natural_habitat),
      tiredness_(TIREDNESS_MAX/2.0)
{}

Troll::~Troll()
{}

ActionResult Troll::action(bool display_info)
{
    // ** Fight first
    if(this->isFighting())
    {
        this->fight(*this->fighter_);
        return EVENT_NULL;
    }
    else
    {
        // ** Decide whether to sleep or fight
        Character* enemy = this->lookForEnemies();
        if(enemy != nullptr)
        {
            if(lab3::utils::eventHappens((double)this->tiredness_/TIREDNESS_MAX))
            {
                this->sleep();
            }
            else
            {
                if(!enemy->isFighting())
                {
                    this->fight(*enemy);
                }
            }
        }
    }
    this->sleep(); // If nothing happens, just sleep
    return EVENT_NULL;
}

bool Troll::isEnemy(const Character &ch) const
{
    return ch.type() != TYPE_TROLL;
}

ActionResult Troll::fight(Character &character)
{
    this->tiredness_ += 2*TIREDNESS_STEP;
    std::stringstream ss;
    ss << this->name()+" fights against "<<character.name()<<", increasing its tiredness up to "<<this->tiredness_;
    lab3::utils_io::print_newline(ss.str());
    return Character::fight(character);
}

ActionResult Troll::sleep()
{
    this->tiredness_ -= TIREDNESS_STEP;
    this->life_points_ += 2*TIREDNESS_STEP;

    std::stringstream ss;
    ss << this->name()+" is sleeping since it's too tired. New tiredness: "<<this->tiredness_<<"; new life: "<<this->life_points_;
    lab3::utils_io::print_newline(ss.str());

    return true;
}
