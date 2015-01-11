#include <places/home.h>

using namespace lab3::places;

Home::Home()
{}

Home::Home(const std::string &name)
    : House(name, true)
{
    this->place_commands_.push_back(CMD_REST);
}

bool Home::enter(Character &character)
{
    lab3::utils_io::wait_for_enter();
    if(character.type() == TYPE_PLAYER)
    {
        if(!character.isAlive()) // The case in which the player is seriously injured
        {
             this->rest(character);
        }
        return Place::enter(character);
    }else
    {
        lab3::utils_io::print_newline(character.name() +" can't enter the Player's house!");
        return false;
    }

}

bool Home::rest(Character &c) const
{
    if(c.getLifePoints() < MAX_LIFE/2.0)
    {
        c.set_life(MAX_LIFE/2.0);
        std::stringstream ss;
        ss << "You rest at home: it's free to sleep! Now you have " << c.getLifePoints() <<std::endl;
        lab3::utils_io::print_newline(ss.str());
        return true;
    }
    else
    {
        lab3::utils_io::print_newline("You have enough life points, it's not time to sleep!");
        return false;
    }
}

Home::~Home()
{}

