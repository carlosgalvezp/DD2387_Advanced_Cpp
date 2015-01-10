#include <places/multi_shop.h>

using namespace lab3::places;


const std::map<std::string, std::vector<int>> health_potions_config =
{
    // Name                      Available units    Extra Points    Price       Weight      Volume
    {"small health potion",     {5,                 10,             5,          5,          5 }},
    {"medium health potion",    {3,                 20,             12,         10,         10}},
    {"big health potion",       {1,                 50,             30,         25,         25}}
};

const std::map<std::string, std::vector<int>> strength_potions_config =
{
    // Name                      Available units    Extra Points    Price       Weight      Volume
    {"small strength potion",     {5,                 10,             5,          5,          5 }},
    {"medium strength potion",    {3,                 20,             12,         10,         10}},
    {"big strength potion",       {1,                 50,             30,         25,         25}}
};

const std::map<std::string, std::vector<int>> bags_config =
{
    // Name                 Units       Price          Volume       Weight      Max volume  Max weight
    {"small bagpack",      {1,          10,             5,          5,          5,          66 }},
    {"medium backpack",    {1,          20,             12,         10,         10,         66}},
    {"big backpack",       {1,          50,             30,         25,         25,         66}}
};

Multi_Shop::Multi_Shop()
{}

Multi_Shop::Multi_Shop(const std::string &name, bool is_open)
    : Shop(name, is_open)
{}

Multi_Shop::~Multi_Shop()
{}

void Multi_Shop::restock()
{
    // ** Call base function
    Shop::restock();

    // ** Clear all the objects
    for(Object *o :objects_)
        delete o;
    objects_.clear();

    // ** Regenerate them
    generateObjects();
}


void Multi_Shop::generateObjects()
{
    // ** Create health and strength potions
    // Create lambda in order to avoid repeating the loop
    auto f = [&](const std::map<std::string, std::vector<int>> map,
                 int potion_type)
    {
        std::map<std::string, std::vector<int>>::const_iterator it;
        std::size_t i = 0;
        for(it = map.begin(); it != map.end(); ++it, ++i)
        {
            for(int j = 0; j < it->second[0]; ++j)          // Number of units
            {
                Object *o;
                if(potion_type == 0) // Can't replace this with function ptr since it's a constructor
                    o = new objects::Health_Potion(it->first, it->second[1], it->second[2], it->second[3], it->second[4]);
                else if(potion_type == 1)
                    o = new objects::Strength_Potion(it->first, it->second[1], it->second[2], it->second[3], it->second[4]);
                else if(potion_type == 2)
                    o = new objects::Container(it->first, it->second[1], it->second[2], it->second[3], it->second[4],it->second[5]);

                this->objects_.push_back(o);
            }
        }
    };

    f(health_potions_config, 0);
    f(strength_potions_config, 1);
    f(bags_config,2);
}

