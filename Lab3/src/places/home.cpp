#include <places/home.h>

using namespace lab3::places;

Home::Home()
{}

Home::Home(const std::string &name)
    : House(name, true)
{}

bool Home::enter(Character &character)
{
    lab3::utils_io::wait_for_enter();
    if(character.type() == TYPE_PLAYER)
    {
        this->rest(character);
        return Place::enter(character);
    }else
    {
        lab3::utils_io::print_newline(character.name() +" can't enter the Player's house!");
        return false;
    }

}

void Home::rest(Character &c) const
{
    c.set_life(MAX_LIFE/2.0);
}

Home::~Home()
{}

