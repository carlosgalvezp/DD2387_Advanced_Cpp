#ifndef ARMORY_H
#define ARMORY_H

#include <places/shop.h>

namespace lab3
{
namespace places{

class Armory : public Shop
{
public:
    Armory();
    Armory(const std::string &name);
    ~Armory();
};

}
}

#endif // ARMORY_H