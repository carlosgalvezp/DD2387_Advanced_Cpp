#include <characters/vampire.h>

using namespace lab3::characters;
using namespace lab3;

int Vampire::id_ = 1;

Vampire::Vampire()
{}

Vampire::Vampire(Place* place, Place* natural_habitat)
    : Animal (std::string(TYPE_VAMPIRE) + std::string(" ")+std::to_string(Vampire::id_++),
              TYPE_VAMPIRE, place, natural_habitat, VAMPIRE_REPRODUCTION_FREQUENCY),
      poison_concentration_(0)
{}

Vampire::~Vampire()
{}

ActionResult Vampire::action(bool display_info)
{
    // ** Fight first
    if(this->isFighting())
    {
        // Decide whether normal fight or bleeding bite
        if(lab3::utils::eventHappens(POISON_PROB))
            this->poison(*this->fighter_);
        else
            this->fight(*this->fighter_);
        return EVENT_NULL;
    }
    else
    {
        return Animal::action(display_info);
    }
    lab3::utils_io::print_newline(this->name() + " is sleeping...");
    return EVENT_NULL;
}

ActionResult Vampire::poison(Character &c)
{
    std::stringstream ss;
    ss << this->name()<<" tries to poison "<<c.name()<<". The poison concentration is "<<this->poison_concentration_;
    lab3::utils_io::print_newline(ss.str());

    // Try to poison
    if(lab3::utils::eventHappens(poison_concentration_))
    {
        std::stringstream ss2;
        ss2 << this->name() <<" has successfully poisoned "<<c.name()<<"! The new poison concentration is "<<this->poison_concentration_;
        lab3::utils_io::print_newline(ss2.str());

        this->poison_concentration_ = std::max(this->poison_concentration_ - POISON_REDUCE_TRY, 0.0);
        c.set_constantly_damaged(CONSTANT_DAMAGE_POISON, POISON_HURT_POINTS);
        return true;
    }
    else
    {
        std::stringstream ss2;
        ss2 << this->name() <<" has failed to poison "<<c.name()<<"! The new poison concentration is "<<this->poison_concentration_;
        lab3::utils_io::print_newline(ss2.str());

        this->poison_concentration_ = std::max(this->poison_concentration_ - POISON_REDUCE_TRY, 0.0);
        return false;
    }
}

double Vampire::getPoisonConcentration()    const{  return this->poison_concentration_;}

bool Vampire::isEnemy(const Character &ch) const
{
    return ch.type() != TYPE_VAMPIRE && ch.type() != TYPE_TROLL; // They don't attack vampires or trolls (they are afraid of them)
}
