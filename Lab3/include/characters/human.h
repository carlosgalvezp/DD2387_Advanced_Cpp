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
    Human(const std::string &name, const std::string &type);
    ~Human();

    virtual bool action() = 0;
    virtual std::string type() const = 0;
};

}
}


#endif // HUMAN_H
