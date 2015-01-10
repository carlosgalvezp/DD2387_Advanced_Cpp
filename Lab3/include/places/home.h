#ifndef HOME_H
#define HOME_H

#include <places/house.h>

namespace lab3
{
namespace places
{
class Home : public House
{
public:
    Home();
    Home(const std::string &name);
    void rest(Character &c) const;
    virtual bool enter(Character &character);
    ~Home();
};

}
}

#endif // HOME_H
