#ifndef ARMORY_H
#define ARMORY_H

#include <places/shop.h>
#include <character.h>

#include <objects/equipment.h>
#include <objects/protection.h>
#include <objects/weapon.h>
#include <characters/human.h>


#define REPAIR_COST 20

namespace lab3
{
namespace places{

class Armory : public Shop
{
public:
    Armory(const std::string &name, bool is_open);

    void generateObjects();
    bool repairEquipment(lab3::characters::Human &p)  const;
    void restock();
    ~Armory();
};

}
}

#endif // ARMORY_H
