#include <characters/wolf.h>

using namespace lab3::characters;
using namespace lab3;

Wolf::Wolf()
{}

Wolf::Wolf(const std::string &name, Place *place, Place *natural_habitat)
    : Animal(name, TYPE_WOLF, place, natural_habitat),
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
        // ** Decide whether fight or look for food
        Character* enemy = this->lookForEnemies();
        if(enemy != nullptr)
        {
            double food_prob = 1;// - this->life_points_ / MAX_LIFE;
            if(lab3::utils::eventHappens(food_prob))
            {
                this->lookForFood();
            }
            else
            {
                if(!enemy->isFighting())
                {
                    this->fight(*enemy);
                }
            }
        }
        else
        {
            this->lookForFood();
        }
    }
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

bool Wolf::isEnemy(const Character &ch) const
{
    return ch.type() != TYPE_WOLF;
}


