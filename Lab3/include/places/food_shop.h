#ifndef FOOD_SHOP_H
#define FOOD_SHOP_H

#include <places/shop.h>
#include <objects/health_potion.h>
#include <objects/strength_potion.h>

// ** Config
// Health potions
#define N_HEALTH_POTIONS    3
#define N_STRENTH_POTIONS   3

namespace lab3
{
namespace places
{
class Food_Shop : public Shop
{
public:
    Food_Shop();
    Food_Shop(const std::string &name, bool is_open);

    void generateObjects();
    ~Food_Shop();
};
}
}



#endif // FOOD_SHOP_H
