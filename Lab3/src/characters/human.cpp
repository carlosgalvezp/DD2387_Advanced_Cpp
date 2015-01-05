#include <characters/human.h>

using namespace lab3::characters;

Human::Human()
{}

Human::Human(const std::string &name, const std::string &type, Place *place)
    : Character(name, type, place)

{
    strength_ = PARAM_HUMAN_STRENGTH;
    defense_  = PARAM_HUMAN_DEFENSE;
}

Human::~Human()
{}

int Human::money()   const   {return this->money_; }

bool Human::buy(Object &o)
{
    if(this->money() > o.price())
    {
        this->pick_up(o);
        std::cout << this->name() <<" has bought a "<<o.name()<<", which costs "<<o.price()
                  <<". Current money: "<<this->money()<<std::endl;
        return true;
    }
    else
    {
        std::cout << this->name() << " can't buy a"<<o.name()<<" since it costs" <<o.price()
                  <<" and the current money is " <<this->money() << std::endl;
        return false;
    }

}

bool Human::sell(Object &o)
{
    this->drop(o);
    int newPrice = o.price()/2;
    this->money_ += newPrice;

    std::cout << this->name() << " has sold a "<<o.name() <<" for "<<newPrice
              <<". Current money: "<<this->money_<<std::endl;

    return true;
}
