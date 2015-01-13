#include <characters/wolf.h>

namespace lab3
{
namespace characters
{

Wolf::Wolf()
{}

Wolf::Wolf(const std::string &name, Place *place)
    : Animal(name, TYPE_WOLF, place)
{}

Wolf::~Wolf()
{}

std::string Wolf::action(bool display_info)
{
    std::cout << "[Wolf::action]"<<std::endl;
    return EVENT_NULL;
}

bool Wolf::bleedingBite(Character &c)
{
    std::stringstream ss;
    ss << this->name()<<" tries a bleeding bite against "<<c.name()<<". The teeth size is "<<this->teeth_size_;
    lab3::utils_io::print_newline(ss.str());

    // Try to poison
    if(lab3::utils::eventHappens((double)this->teeth_size_/WOLF_MAX_TEETH_SIZE))
    {
        std::stringstream ss2;
        ss2 << this->name() <<" has successfully bitten "<<c.name()<<", who is now bleeding";
        lab3::utils_io::print_newline(ss2.str());

        c.set_constantly_damaged(CONSTANT_DAMAGE_BLEED, BLEED_HURT_POINTS);
        return true;
    }
    else
    {
        std::stringstream ss2;
        ss2 << this->name() <<" has failed to bite "<<c.name()<<"!";
        lab3::utils_io::print_newline(ss2.str());

        return false;
    }
}

}
}


