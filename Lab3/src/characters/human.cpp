#include <characters/human.h>
#include <objects/usable.h>
using namespace lab3::characters;

Human::Human()
{}

Human::Human(const std::string &name, const std::string &type, Place *place)
    : Character(name, type, place)

{}

Human::~Human()
{}

std::string Human::action(bool display_info)
{
    return EVENT_NULL;
}
int Human::getMoney()   const   {return this->money_; }

void Human::addMoney(int money)
{
    this->money_ += money;
}

bool Human::buy(Object &o)
{
    if(this->getMoney() > o.price())
    {
        if(this->pick_up(o))
        {
            this->money_ -= o.price();
            std::cout << this->name() <<" has bought a "<<o.name()<<", which costs "<<o.price()
                      <<". Current money: "<<this->getMoney()<<std::endl;
            return true;
        }
    }
    else
    {
        std::cout << this->name() << " can't buy a"<<o.name()<<" since it costs" <<o.price()
                  <<" and the current money is " <<this->getMoney() << std::endl;
    }
    return false;
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

bool Human::use(Object &o)
{
    std::cout << "[Human::use] TO DO" << std::endl;
    return true;
}
