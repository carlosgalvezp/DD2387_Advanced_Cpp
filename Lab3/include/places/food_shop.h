#ifndef FOOD_SHOP_H
#define FOOD_SHOP_H

#include <places/shop.h>

namespace lab3
{
namespace places
{
class Food_Shop : public Shop
{
public:
    Food_Shop();
    Food_Shop(const std::string &name);
    ~Food_Shop();
};
}
}



#endif // FOOD_SHOP_H
