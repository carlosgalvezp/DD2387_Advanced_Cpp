#ifndef SHOP_H
#define SHOP_H

#include <places/indoor.h>

namespace lab3
{
namespace places
{
class Shop : public Indoor
{
public:
    Shop();
    Shop(const std::string &name, bool is_open);
    ~Shop();
};
}
}



#endif // SHOP_H
