#include <characters/vampire.h>

using namespace lab3::characters;

Vampire::Vampire()
{}

Vampire::Vampire(const std::string &name, Place* place)
    : Animal (name, TYPE_VAMPIRE, place)
{}

Vampire::~Vampire()
{}

std::string Vampire::action(bool display_info)
{
    std::cout << "[Vampire::action]"<<std::endl;
    return EVENT_NULL;
}

bool Vampire::poison(Character &c)
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
