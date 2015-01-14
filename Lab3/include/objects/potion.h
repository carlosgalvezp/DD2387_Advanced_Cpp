#ifndef POTION_H
#define POTION_H

#include <objects/usable.h>
//#include <characters/player.h>

namespace lab3
{
namespace objects
{

class Potion : public Usable
{
public:
    Potion(const std::string &name,
           const std::string &description,
           int extra_points,
           int price,
           int volume,
           int weight);

    ActionResult use(Character &c);
    ~Potion();

protected:
    int extra_points_;
};

}
}

#endif // POTION_H
