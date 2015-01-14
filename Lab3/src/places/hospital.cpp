#include <places/hospital.h>

using namespace lab3::places;


Hospital::Hospital(const std::string &name)
    : Indoor(name, true)
{
    this->place_commands_.push_back(CMD_CURE);
}

Hospital::~Hospital()
{}

bool Hospital::cure(characters::Human &c) const
{
    std::stringstream ss;
    if(c.getLifePoints() == MAX_LIFE)
    {
        lab3::utils_io::print_newline("You have already the maximum number of life points, go fight some monsters!");
        return false;
    }
    else if(c.getMoney() >= CURE_PRICE)
    {
        c.set_life(MAX_LIFE);
        c.remove_constantly_damaged();
        c.addMoney(-CURE_PRICE);
        ss << "You have been cured at the Hospital with a cost of "<<CURE_PRICE
           <<". Now you have "<<c.getLifePoints()<<" life points";
        lab3::utils_io::print_newline(ss.str());
        return true;
    }
    else
    {        
        ss << "The Hospital costs "<<CURE_PRICE<<" but you only have " <<c.getMoney();
        lab3::utils_io::print_newline(ss.str());
        return false;
    }
}

