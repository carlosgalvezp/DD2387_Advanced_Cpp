#include <places/armory.h>

using namespace lab3::places;

const std::map<std::string, std::vector<int>> weapons_config =
{
    // Name                     Hands required    Extra Points    Price       Weight      Volume
    {"dagger",                 {1,                 10,             5,          5,          5 }},
    {"sword",                  {1,                 20,             12,         10,         10}},
    {"long sword",             {2,                 30,             20,         15,         20}},
    {"bow",                    {2,                 20,             12,         10,         10}},
    {"axe",                    {2,                 20,             20,         25,         15}}
};

const std::map<std::string, std::vector<int>> protections_config =
{
    // Name          Extra Points       Price           Weight      Volume
    {"helmet",      {5,                  10,             5,          5,          }},
    {"shield",      {10,                 20,             10,         5,          }},
    {"chainmail",   {15,                 30,             15,         10,         }},
    {"armor",       {20,                 40,             20,         15,         }}
};


Armory::Armory(const std::string &name, bool is_open)
    : Shop(name, is_open)
{
    this->place_commands_.push_back(CMD_REPAIR);
}

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
    auto f = [this](const std::map<std::string, std::vector<int>> map,
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
            this->objects_.push_back(o);
        }
    };

    f(weapons_config, 0);
    f(protections_config, 1);
}

bool Armory::repairEquipment(lab3::characters::Human &p) const
{    
    if(p.getMoney() >= REPAIR_COST)
    {
        for(Object* o : p.objects())
        {
            lab3::objects::Equipment* o_equip = dynamic_cast<lab3::objects::Equipment*>(o);
            if(o_equip != nullptr)    // Check for Equipment only
            {
                o_equip->repair();
            }
        }
        p.addMoney(-REPAIR_COST);
        std::stringstream ss;
        ss << "You have repaired your equipment for a cost of "<<REPAIR_COST;
        lab3::utils_io::print_newline(ss.str());
        return true;
    }
    else
    {
        std::stringstream ss;
        ss << "You cannot repair your equipment since you have "<<p.getMoney()<< " of money and this costs "<<REPAIR_COST;
        lab3::utils_io::print_newline(ss.str());
        return false;
    }
}
