#include <characters/princess.h>

using namespace lab3::characters;

Princess::Princess()
{}

Princess::Princess(const std::string &name)
    : Human(name, TYPE_PRINCESS)
{}

Princess::~Princess()
{

}

bool Princess::action()
{
    lab3::utils_io::print_newline("Princess action [TO DO]");
    return false;
}

std::string Princess::type() const
{
    return "Princess";
}
