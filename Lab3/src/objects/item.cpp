#include <objects/item.h>
using namespace lab3::objects;

Item::Item()
{}

Item::Item(const std::string &name,
           const std::string &description,
           int price,
           int weight,
           int volume)
    : Object(name, description, price, weight, volume)
{}

Item::~Item()
{}

bool Item::use(Character &c)
{
    if(this->name() == "torch")
    {
        if(c.currentPlace()->name() == NAME_CAVE)
        {
            throw std::runtime_error(EVENT_TORCH_ON);
        }
        else
        {
            lab3::utils_io::print_newline("You cannot use the torch here, it's already light enough.");
            return false;
        }
    }
    return true;
}

