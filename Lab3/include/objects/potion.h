#ifndef POTION_H
#define POTION_H

#include <objects/item.h>
//#include <characters/player.h>

namespace lab3
{
namespace objects
{

class Potion : public Item
{
public:
    Potion();
    Potion(const std::string &name,
           const std::string &description,
           int extra_points,
           int price,
           int volume,
           int weight);

//    virtual void use(lab3::characters::Player &player);
    ~Potion();

protected:
    int extra_points_;
};

}
}

#endif // POTION_H
