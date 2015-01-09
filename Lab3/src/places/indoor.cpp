#include <places/indoor.h>

using namespace lab3::places;

Indoor::Indoor()
{}

Indoor::Indoor(const std::string &name, bool is_open)
    : Place(name), is_open_(is_open)
{}


Indoor::~Indoor()
{}

bool Indoor::isOpen() const {return this->is_open_;}

void Indoor::setOpen(bool open){ this->is_open_ = open;}

bool Indoor::enter(Character &character)
{
    // ** Check if door open
    if(this->isOpen())
    {
        return Place::enter(character);
    }
    else
    {
        lab3::utils_io::print_newline("You cannot enter the "+this->name()+", since it's closed.");
        return false;
    }
}
