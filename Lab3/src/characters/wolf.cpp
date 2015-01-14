#include <characters/wolf.h>

using namespace lab3::characters;
using namespace lab3;

int Wolf::id_ = 1;

Wolf::Wolf(Place *place, Place *natural_habitat)
    : Animal(std::string(TYPE_WOLF) + std::string(" ")+std::to_string(Wolf::id_++),
             TYPE_WOLF, place, natural_habitat, WOLF_REPRODUCTION_FREQUENCY),
      teeth_size_(0)
{}

Wolf::~Wolf()
{}

ActionResult Wolf::action(bool display_info)
{
    // ** Fight first
    if(this->isFighting())
    {
        // Decide whether normal fight or bleeding bite
        if(lab3::utils::eventHappens(BLEED_HURT_PROB))
            this->bleedingBite(*this->fighter_);
        else
            this->fight(*this->fighter_);
        return EVENT_NULL;
    }
    else
    {
        return Animal::action(display_info);
    }
    return EVENT_NULL;
}

bool Wolf::bleedingBite(Character &c)   const
{
    std::stringstream ss;
    ss << this->name()<<" tries a bleeding bite against "<<c.name()<<". The teeth size is "<<this->teeth_size_;
    lab3::utils_io::print_newline(ss.str());

    // Try to poison
    if(lab3::utils::eventHappens((double)this->teeth_size_/WOLF_MAX_TEETH_SIZE))
    {
        std::stringstream ss2;
        ss2 << this->name() <<" has successfully bitten "<<c.name()<<", who is now bleeding and loses "<< BLEED_HURT_POINTS;
        lab3::utils_io::print_newline(ss2.str());

        c.add_life(-BLEED_HURT_POINTS);
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

bool Wolf::isEnemy(const Character &ch) const
{
    return ch.type() != TYPE_WOLF;
}

Character* Wolf::reproduce()
{
    if(this->current_place_ == this->natural_habitat_ &&
       this->days_since_last_reproduced_++ > this->reproduction_frequency_)
    {
        lab3::utils_io::print_newline("============ " + this->name()+ " has reproduced! ============");
        lab3::utils_io::wait_for_enter();
        this->days_since_last_reproduced_ = 0;
        return new Wolf(this->currentPlace(), this->currentPlace());
    }
    return nullptr;
}

