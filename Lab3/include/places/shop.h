#ifndef SHOP_H
#define SHOP_H

#include <places/indoor.h>

#define DAYS_TO_RESTOCK 5

namespace lab3
{
namespace places
{
class Shop : public Indoor
{
public:
    Shop();
    Shop(const std::string &name, bool is_open);

    virtual void restock();

    ~Shop();

protected:
    int days_to_restock_;
};
}
}



#endif // SHOP_H
