#include "character.h"

using namespace lab3;

Character::Character()
{}

Character::Character(const std::string &name, const std::string &type, Place *place)
    : name_(name),
      type_(type),
      current_place_(place),
      life_points_(MAX_LIFE),
      initiative_(DEFAULT_INITIATIVE),
      is_fighting_(false)
{
}

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

bool Character::pick_up(lab3::Object &object)
{
    std::cout << "======== Character::pick_up [TO DO] ========"<<std::endl;
    return true;
}

bool Character::drop(lab3::Object &object)
{
    this->current_place_->drop(object);
    return true;
}

void Character::talk_to(Character *character)
{
    int n_msg = 0; // Make this dynamic! XXXXXX
    std::string msg = "[" + this->name()+"] " + this->getTalkMessages()[n_msg];
    lab3::utils_io::print_newline(msg);
}


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
const std::vector<std::string>& Character::getCommands()      const { return this->commands_;}
const std::vector<std::string>& Character::getTalkMessages()  const { return this->talk_msgs_;}

std::string Character::name()     const{    return this->name_;        }

const Place* Character::currentPlace()      const           {    return this->current_place_;    }
      Place* Character::currentPlace()                      {    return this->current_place_;    }

const std::vector<Object*>& Character::objects()  const {    return this->objects_;          }
      std::vector<Object*>& Character::objects()        {    return this->objects_;          }

bool Character::operator ==(const Character &obj) const
{
    return this->name() == obj.name();
}

bool Character::operator !=(const Character &obj) const
{
    return !this->operator ==(obj);
}
