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
    Home(const std::string &name);
    ~Home();

    virtual bool enter(Character &character);
    bool rest(Character &c) const;
};

}
}

#endif // HOME_H
