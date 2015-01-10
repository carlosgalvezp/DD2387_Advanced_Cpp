#include <objects/usable.h>

using namespace lab3::objects;

Usable::Usable()
{}

Usable::Usable(const std::string &name,
               const std::string &description,
               int price,
               int weight,
               int volume,
               bool is_single_use)
    : Object(name, description, price, weight, volume),
      is_single_use_(is_single_use)
{}

Usable::~Usable()
{}

bool Usable::isSingleUse() const  {   return this->is_single_use_;}

bool Usable::use(Character &c)
{
    std::cout<< "[Usable::use]"<<std::endl;
    return true;
}

