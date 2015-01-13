#include "character.h"
#include <places/indoor.h>

using namespace lab3;

const std::map<std::string, std::vector<int>> attributes =
{ // Type                    Life       Strength    Defense     Initiative
    {TYPE_PLAYER,           {50,        20,         15,         10}},
    {TYPE_PRINCESS,         {50,        20,         15,         10}},
    {TYPE_WIZARD,           {50,        20,         15,         10}},
    {TYPE_HUMAN,            {50,        20,         15,         10}},
    {TYPE_TROLL,            {50,        20,         15,         10}},
    {TYPE_WOLF,             {50,        20,          5,         10}},
    {TYPE_VAMPIRE,          {50,        15,          5,         10}},
    {TYPE_FINAL_MONSTER,    {100,       50,         0,         10}}
};

Character::Character()
{}

Character::Character(const std::string &name, const std::string &type, Place *place)
    : name_(name),
      type_(type),
      current_place_(place),
      is_fighting_(false),
      n_msg_talk_(0),
      constant_damage_points_(0),
      constant_damage_type_("")
{
    // ** Set attributes
    this->life_points_ = attributes.at(type)[0];
    this->strength_    = attributes.at(type)[1];
    this->defense_     = attributes.at(type)[2];
    this->initiative_  = attributes.at(type)[3];

    place->addCharacter(*this);
}

Character::~Character()
{
    for(Object *o : objects_)
    {
        if(o != nullptr)
        {
            delete o;
            o = nullptr;
        }
    }
}

std::string Character::type()     const { return this->type_;           }
std::string Character::name()     const {    return this->name_;        }

bool Character::isConstantlyDamaged() const{ return this->constant_damage_points_ > 0;}

bool Character::go(const std::string& direction)
{
    // ** Get available directions
    std::map<std::string, Place*> directions = this->current_place_->directions();

    // ** Check if the given direction is available
    Place *new_place;
    if(directions.find(direction) != directions.end())
    {
        new_place = directions.at(direction);
        return new_place->enter(*this);
    }
    return false;
}

bool Character::fight(Character &character)
{
    if(!this->isFighting())
    {
        this->is_fighting_ = true;
        this->fighter_ = &character;
    }
    if(!character.isFighting())
    {
        character.is_fighting_ = true;
        character.fighter_ = this;
    }

    // XXXX Include randomnesss
    lab3::utils_io::print_newline("-------- Fight between "+this->name() +" and "+character.name());
    lab3::utils_io::wait_for_enter();
    std::stringstream ss;
    ss<< "["<<this->name()<<"] Life: "<<this->getLifePoints()<<"; Strength: "<<this->getStrength()<<"; Defense: "<< this->getDefense()<<std::endl;
    ss<< "["<<character.name()<<"] Life: "<<character.getLifePoints()<<"; Strength: "<<character.getStrength()<<"; Defense: "<< character.getDefense()<<std::endl;

    lab3::utils_io::print_newline(ss.str());


    int damage = computeDamage(*this, character);
    character.set_damage(damage);

    std::cout << this->name() <<" attacks "<<character.name()<<", who is injured and loses "<<damage<<" life points"<<std::endl;
    lab3::utils_io::wait_for_enter();

    if(!character.isAlive())             // The oponent died
    {
        if(character.type() != TYPE_PLAYER)
            lab3::utils_io::print_newline(character.name() + " has died");
        else
            lab3::utils_io::print_newline(character.name() + " has been seriously injured");
        this->is_fighting_ = false;
        character.is_fighting_ = false;
        return true;
    }
    else if(!character.isFighting())    // The oponent scaped
    {
        lab3::utils_io::print_newline(character.name() + " has scaped the fight");
        this->is_fighting_ = false;
        character.is_fighting_ = false;
        return true;
    }
    return false;
}

bool Character::scape()
{
    lab3::utils_io::print_newline(this->name_ + " has scaped the fight");
    this->is_fighting_ = false;
    this->fighter_->is_fighting_ = false;
//    this->fighter_->fighter_ = nullptr;
//    this->fighter_ = nullptr;
    return true;
}

bool Character::pick_up(lab3::Object &object)
{
    // ** Find it in the objects vector
    this->current_place_->pick_up(object);
    this->objects_.push_back(&object);

    lab3::utils_io::print_newline("The character "+this->name()+" has picked up a "+object.name()+" from the "+this->currentPlace()->name());
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

void Character::talk_to(Character &character)
{
    std::string msg = "[" + this->name()+"] talks to " + character.name()+":\n"
            + "\""+this->getTalkMessages()[n_msg_talk_++%this->getTalkMessages().size()]+"\"";
    lab3::utils_io::print_newline(msg);
}


// ** Setters
void Character::set_place(Place *p)         {    this->current_place_ = p;}
void Character::set_fighting(bool fighting) {    this->is_fighting_ = fighting;}
void Character::set_damage(int damage)
{
    this->life_points_ -= damage;
}

void Character::set_life(int life)
{
    this->life_points_ = life;
}

void Character::add_life(int life)
{
    this->life_points_ = std::min(this->life_points_ + life, MAX_LIFE); // XXX CHANGE so that every player has its own
    std::stringstream ss;
    ss << "The character "<<this->name()<<" gains "<<life<<" life points, so it now has "<<this->life_points_<<" life points";
    lab3::utils_io::print_newline(ss.str());
}

void Character::add_strength(int strength)
{
    this->life_points_ = std::min(this->strength_ + strength, MAX_STRENGTH); // XXX CHANGE so that every player has its own
    std::stringstream ss;
    ss << "The character "<<this->name()<<" gains "<<strength<<" strength points, so it now has "<<this->strength_<<" strength points";
    lab3::utils_io::print_newline(ss.str());
}

void Character::set_talk_msgs(const std::vector<std::string> &msgs)
{
    this->talk_msgs_ = msgs;
}

void Character::set_constantly_damaged(const std::string &type, int points)
{
    std::stringstream ss;
    ss << "The character "<<this->name()<< "is now "<<type<<"! It will lose "<<points<<" after each turn";
    lab3::utils_io::print_newline(ss.str());

    this->constant_damage_type_ = type;
    this->constant_damage_points_ = 0;
}

// ** Accessors
int Character::getLifePoints()    const{    return this->life_points_; }
int Character::getStrength()      const{    return this->strength_;    }
int Character::getDefense()       const{    return this->defense_;     }
int Character::getInitiative()    const{    return this->initiative_;  }

bool Character::isAlive()         const{    return this->getLifePoints() > 0;}
bool Character::isFighting()      const{    return this->is_fighting_;}

const std::vector<std::string>& Character::getCommands()      const
{
    // ** Get commands from place
    return this->currentPlace()->getCommands();
}
const std::vector<std::string>& Character::getTalkMessages()  const { return this->talk_msgs_;}


const Place* Character::currentPlace()      const           {    return this->current_place_;    }
      Place* Character::currentPlace()                      {    return this->current_place_;    }

const std::vector<Object*>& Character::objects()  const {    return this->objects_;          }
      std::vector<Object*>& Character::objects()        {    return this->objects_;          }

Character* Character::fighter() {return this->fighter_;}

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
