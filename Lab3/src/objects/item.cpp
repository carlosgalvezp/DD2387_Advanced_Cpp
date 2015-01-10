#include <objects/item.h>
using namespace lab3::objects;

Item::Item()
{}

Item::Item(const std::string &name,
           const std::string &description,
           int price,
           int weight,
           int volume,
           bool is_single_use)
    : Object(name, description, price, weight, volume),
      is_single_use_(is_single_use)
{}

Item::~Item()
{}

bool Item::isSingleUse() const  {   return this->is_single_use_;}

bool Item::use(Character &c)
{
    std::cout<< "[Item::use]"<<std::endl;
    return true;
}

