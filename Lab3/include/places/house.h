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
    House(const std::string &name, bool is_open);
    ~House();

    virtual bool enter(Character &character);

};
}
}


#endif // HOME_H
