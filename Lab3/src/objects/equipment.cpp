#include <objects/equipment.h>

using namespace lab3::objects;

Equipment::Equipment(const std::string &name,
                     const std::string &description,
                     int price,
                     int volume,
                     int weight)
    :   Object(name, description, price, volume, weight),
        wear_(0)
{}

int Equipment::wear() const {return this->wear_;}

void Equipment::repair()    { this->wear_ = 0; }


Equipment::~Equipment()
{}

