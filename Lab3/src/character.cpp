#include "character.h"

using namespace lab3;

Character::Character()
{}

Character::Character(const std::string &name, const std::string &type)
    : name_(name), type_(type), life_points_(MAX_LIFE)
{}

Character::~Character()
{}

//void Character::action();
bool Character::go(const std::string& direction)
{
    // ** Get available directions
    std::map<std::string, Place*> directions = this->current_place_->directions();

    // ** Check if the given direction is available
    Place *new_place;
    try
    {
        new_place = directions.at(direction);
    }
    catch(std::out_of_range &e)
    {
        return false;
    }

    // ** Enter the place
    new_place->enter(*this);
    return true;
}

//void Character::fight(Character &character)
//{

//}

//void pick_up(lab3::Object &object);
//void drop(lab3::Object &object);
//void talk_to(Character &character);


void Character::set_place(Place *p)
{
    this->current_place_ = p;
}

// ** Accessors
int Character::getLifePoints()    const{    return this->life_points_; }
int Character::getStrength()      const{    return this->strength_;    }
int Character::getDefense()       const{    return this->defense_;     }
int Character::getInitiative()    const{    return this->initiative_;  }

bool Character::isAlive()         const{    return this->getLifePoints() > 0;}

const std::vector<std::string>& Character::getBasicCommands() const { return this->basic_commands_;}

std::string Character::name()     const{    return this->name_;        }

Place* Character::currentPlace() {    return this->current_place_;    }

bool Character::operator ==(const Character &obj) const
{
    return this->name() == obj.name();
}
