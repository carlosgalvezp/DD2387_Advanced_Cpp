#include <characters/princess.h>

using namespace lab3::characters;

Princess::Princess()
{}

Princess::Princess(const std::string &name, Place *place)
    : Human(name, TYPE_PRINCESS, place)
{
    this->talk_msgs_ =
    {
        "Please help me, I am trapped here!",
        "You need to defeat the final monster in order to free me!"
    };
}

Princess::~Princess()
{

}

std::string Princess::action(bool display_info)
{
    if(display_info)
    {
        lab3::utils_io::print_newline("Princess action [TO DO]");
    }
    return EVENT_NULL;
}

std::string Princess::type() const
{
    return "Princess";
}
