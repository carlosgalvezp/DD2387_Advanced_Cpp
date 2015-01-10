#include <objects/key.h>

using namespace lab3::objects;

Key::Key()
{}

Key::Key(const std::string &name, Place *place)
    : Item(name, "It opens a specific door",100,0,0, false), place_(place)
{}

Key::~Key()
{}

bool Key::use(Character &c)
{
    // ** Check if the current place is an indoor place
    lab3::places::Indoor* place_ptr = dynamic_cast<lab3::places::Indoor*>(c.currentPlace());
    if(place_ptr != nullptr)
    {
        // ** Check if the place is the same
        if(*place_ptr == *c.currentPlace())
        {
            place_ptr->setOpen(true);
            lab3::utils_io::print_newline("You have successfully opened the " + place_ptr->name());
            return true;
        }
        else
        {
            lab3::utils_io::print_newline("The key cannot open this place");
        }
    }
    else
    {
        lab3::utils_io::print_newline("Can't use the key here");
    }
    return false;
}



