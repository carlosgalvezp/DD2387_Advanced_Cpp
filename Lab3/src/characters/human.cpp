#include <characters/human.h>
#include <objects/usable.h>
using namespace lab3::characters;

Human::Human(const std::string &name, const std::string &type, Place *place)
    : Character(name, type, place)

{}

Human::~Human()
{}

int Human::getMoney()   const   {return this->money_; }

void Human::addMoney(int money)
{
    this->money_ += money;
}

ActionResult Human::buy(Object &o)
{
    if(this->getMoney() > o.price())
    {
        if(this->pick_up(o).success_)
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

ActionResult Human::sell(Object &o)
{
    this->drop(o);
    int newPrice = o.price()/2;
    this->money_ += newPrice;

    std::cout << this->name() << " has sold a "<<o.name() <<" for "<<newPrice
              <<". Current money: "<<this->money_<<std::endl;

    return true;
}

ActionResult Human::use(Object &o)
{
    std::cout << "[Human::use]" << std::endl;
    return true;
}

bool Human::isEnemy(const Character &ch) const
{
    return ch.type() != TYPE_HUMAN && ch.type() != TYPE_WIZARD && ch.type() != TYPE_PLAYER;
}
