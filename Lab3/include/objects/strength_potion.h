#ifndef STRENGTH_POTION_H
#define STRENGTH_POTION_H

#include <objects/potion.h>

namespace lab3
{
namespace objects
{

class Strength_Potion : public Potion
{
public:
    Strength_Potion(const std::string &name,
                    int extra_points,
                    int price,
                    int volume,
                    int weight);

    ActionResult use(Character &c);
    ~Strength_Potion();
};

}
}

#endif // STRENGTH_POTION_H
