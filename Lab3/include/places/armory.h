#ifndef ARMORY_H
#define ARMORY_H

#include <places/shop.h>
#include <character.h>

#include <objects/equipment.h>
#include <objects/protection.h>
#include <objects/weapon.h>

namespace lab3
{
namespace places{

class Armory : public Shop
{
public:
    Armory();
    Armory(const std::string &name, bool is_open);

    void generateObjects();
    void repairEquipment(Character &p)  const;
    void restock();
    ~Armory();
};

}
}

#endif // ARMORY_H
