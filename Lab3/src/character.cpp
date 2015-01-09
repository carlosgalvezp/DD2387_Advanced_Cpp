#include "character.h"

using namespace lab3;

const std::map<std::string, std::vector<int>> attributes =
{ // Type                    Life       Strength    Defense     Initiative
    {TYPE_PLAYER,           {50,        20,         15,         10}},
    {TYPE_PRINCESS,         {50,        20,         15,         10}},
    {TYPE_WIZARD,           {50,        20,         15,         10}},
    {TYPE_HUMAN,            {50,        20,         15,         10}},
    {TYPE_TROLL,            {50,        20,         15,         10}},
    {TYPE_WOLF,             {50,        20,         15,         10}},
    {TYPE_VAMPIRE,          {50,        20,         15,         10}},
    {TYPE_FINAL_MONSTER,    {100,       50,         50,         10}}
};

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
    // ** Set attributes
    this->life_points_ = attributes.at(type)[0];
    this->strength_    = attributes.at(type)[1];
    this->defense_     = attributes.at(type)[2];
    this->initiative_  = attributes.at(type)[3];

    place->enter(*this);
}

Character::~Character()
{}

std::string Character::type() const { return this->type_;}

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

bool Character::fight(Character &character)
{
    if(!this->isFighting())
        this->is_fighting_ = true;
    if(!character.isFighting())
        character.is_fighting_ = true;

    // XXXX Include randomnesss
    lab3::utils_io::print_newline("-------- Fight between "+this->name() +" and "+character.name());
    std::stringstream ss;
    ss<< "["<<this->name()<<"] Life: "<<this->getLifePoints()<<"; Strength: "<<this->getStrength()<<"; Defense: "<< this->getDefense()<<std::endl;
    ss<< "["<<character.name()<<"] Life: "<<character.getLifePoints()<<"; Strength: "<<character.getStrength()<<"; Defense: "<< character.getDefense()<<std::endl;

    lab3::utils_io::print_newline(ss.str());


    int damage = computeDamage(*this, character);
    character.set_damage(damage);

    std::cout << this->name() <<" attacks "<<character.name()<<", who is injured and loses "<<damage<<" life points"<<std::endl;
    lab3::utils_io::wait_for_enter();

    if(!character.isAlive())
    {
        lab3::utils_io::print_newline(character.name() + " has died");
        return true;
    }
    else if(!character.isFighting())
    {
        lab3::utils_io::print_newline(character.name() + " has scaped the fight");
        return true;
    }
    else
    {
        return character.fight(*this);      // The other character fights back
    }
    return false;
}

bool Character::pick_up(lab3::Object &object)
{
    // ** Find it in the objects vector
    this->current_place_->pick_up(object);
    this->objects_.push_back(&object);

    return true;
}

bool Character::drop(lab3::Object &object)
{
    // ** Find it in the objects vector
    auto it = std::find(objects_.begin(), objects_.end(), &object);
    if(it != objects_.end())
    {
        objects_.erase(it);
    }
    this->current_place_->drop(object);

    return true;
}

void Character::talk_to(Character *character)
{
    int n_msg = 0; // Make this dynamic! XXXXXX
    std::string msg = "[" + this->name()+"] " + this->getTalkMessages()[n_msg];
    lab3::utils_io::print_newline(msg);
}


// ** Setters
void Character::set_place(Place *p)         {    this->current_place_ = p;}
void Character::set_fighting(bool fighting) {    this->is_fighting_ = fighting;}
void Character::set_damage(int damage)
{
    this->life_points_ -= damage;
}

void Character::add_life(int life)
{
    this->life_points_ = std::min(this->life_points_ + life, MAX_LIFE); // XXX CHANGE so that every player has its own
}

void Character::add_strength(int stregth)
{
    this->life_points_ = std::min(this->strength_ + stregth, MAX_STRENGTH); // XXX CHANGE so that every player has its own
}

// ** Accessors
int Character::getLifePoints()    const{    return this->life_points_; }
int Character::getStrength()      const{    return this->strength_;    }
int Character::getDefense()       const{    return this->defense_;     }
int Character::getInitiative()    const{    return this->initiative_;  }

bool Character::isAlive()         const{    return this->getLifePoints() > 0;}
bool Character::isFighting()      const{    return this->is_fighting_;}

const std::vector<std::string>& Character::getBasicCommands() const { return this->basic_commands_;}
std::vector<std::string> Character::getCommands()      const { return this->commands_;}
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

int lab3::computeDamage(const Character &attacker, const Character &defender)
{
    return std::max(0, attacker.getStrength() - defender.getDefense());
}
