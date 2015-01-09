#include <places/armory.h>

using namespace lab3::places;

const std::map<std::string, std::vector<int>> weapons_config = // XXXXXX CONFIG THIS!!!
{
    // Name                     Hands required    Extra Points    Price       Weight      Volume
    {"dagger",                 {1,                 10,             5,          5,          5 }},
    {"sword",                  {1,                 20,             12,         10,         10}},
    {"long sword",             {2,                 20,             12,         10,         10}},
    {"bow",                    {2,                 20,             12,         10,         10}},
    {"axe",                    {2,                 50,             30,         25,         25}}
};

const std::map<std::string, std::vector<int>> protections_config =
{
    // Name          Extra Points       Price           Weight      Volume
    {"helmet",      {5,                 10,             5,          5,          5 }},
    {"shield",      {1,                 50,             30,         25,         25}},
    {"chainmail",   {1,                 50,             30,         25,         25}},
    {"armor",       {3,                 20,             12,         10,         10}}
};


Armory::Armory()
{}

Armory::Armory(const std::string &name, bool is_open)
    : Shop(name, is_open)
{}

Armory::~Armory()
{}

void Armory::restock()
{
    // Do nothing; the armory won't restock
}

void Armory::generateObjects()
{
    // ** Create health and strength potions
    // Create lambda in order to avoid repeating the loop
    auto f = [&](const std::map<std::string, std::vector<int>> map,
                 int obj_type)
    {
        std::map<std::string, std::vector<int>>::const_iterator it;
        std::size_t i = 0;
        for(it = map.begin(); it != map.end(); ++it, ++i)
        {
            Object *o;
            if(obj_type == 0)
                o = new objects::Weapon(it->first, it->second[0], it->second[1], it->second[2], it->second[3], it->second[4]);
            else
                o = new objects::Protection(it->first, it->second[0], it->second[1], it->second[2], it->second[3]);
            objects_.push_back(o);
        }
    };

    f(weapons_config, 0);
    f(protections_config, 1);
}

void Armory::repairEquipment(Character &p) const
{
    for(Object* o : p.objects())
    {
        lab3::objects::Equipment* o_equip = dynamic_cast<lab3::objects::Equipment*>(o);
        if(o_equip != nullptr)    // Check for Equipment only
        {
            o_equip->repair();
        }
    }
}
