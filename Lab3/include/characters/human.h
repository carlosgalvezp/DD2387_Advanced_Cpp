#ifndef HUMAN_H
#define HUMAN_H

#include <character.h>

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

    virtual bool action() = 0;
    virtual std::string type() const = 0;

    int getMoney()      const;

    bool buy(Object* o);
    bool sell(Object* o);
    bool use(Object* o);

protected:
    int money_;
};

}
}


#endif // HUMAN_H
