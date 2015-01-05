#ifndef SHOP_H
#define SHOP_H

#include <place.h>

namespace lab3
{
namespace places
{
class Shop : public Place
{
public:
    Shop();
    Shop(const std::string &name);
    ~Shop();
};
}
}



#endif // SHOP_H
