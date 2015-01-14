#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

#include <objects/potion.h>

namespace lab3
{
namespace objects
{

class Health_Potion : public Potion
{
public:
    Health_Potion(const std::string &name,
                  int extra_points,
                  int price,
                  int weight,
                  int volume);

    ActionResult use(Character &c);

    ~Health_Potion();
};

}
}


#endif // HEALTH_POTION_H
