#ifndef HOUSE_H
#define HOUSE_H

#include <places/indoor.h>

namespace lab3
{
namespace places
{

class House : public Indoor
{
public:
    House();
    House(const std::string &name, bool is_open);

    virtual bool enter(Character &character);

    ~House();
};
}
}


#endif // HOME_H
