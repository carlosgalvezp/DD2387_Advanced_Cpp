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

    std::string action(bool display_info) = 0;

    int getMoney()              const;
    void addMoney(int money);

    bool isEnemy(const Character &ch) const;

    bool buy(Object &o);
    bool sell(Object &o);
    bool use(Object &o);

protected:
    int money_;     // Only humans can buy stuff
    int courage_;   // The more courage, the more it's likely to fight
};

}
}


#endif // HUMAN_H
