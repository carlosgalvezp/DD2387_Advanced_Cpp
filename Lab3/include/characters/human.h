#ifndef HUMAN_H
#define HUMAN_H

#include <character.h>
#include <places/shop.h>
#define PARAM_HUMAN_STRENGTH    20
#define PARAM_HUMAN_DEFENSE     10

#define DEFAULT_MONEY           50

namespace lab3
{
namespace characters
{

class Human : public Character
{
public:
    Human();
    Human(const std::string &name, const std::string &type, Place *p);
    ~Human();

    virtual std::string action(bool display_info);
//    virtual std::string type() const = 0;

    int getMoney()      const;
    void addMoney(int money);


    bool buy(Object &o);
    bool sell(Object &o);
    bool use(Object &o);

protected:
    int money_;
};

}
}


#endif // HUMAN_H
