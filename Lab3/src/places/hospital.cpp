#include <places/hospital.h>

using namespace lab3::places;

Hospital::Hospital()
{}

Hospital::Hospital(const std::string &name)
    : Indoor(name, true)
{}

Hospital::~Hospital()
{}

bool Hospital::cure(characters::Human &c) const
{
    if(c.getMoney() >= CURE_PRICE)
    {
        c.addMoney(-CURE_PRICE);
        std::cout << "You have been cured at the Hospital with a cost of "<<CURE_PRICE<<std::endl;
        return true;
    }
    else
    {
        std::cout << "The Hospital costs "<<CURE_PRICE<<" but you only have " <<c.getMoney()<<std::endl;
        return false;
    }
}

