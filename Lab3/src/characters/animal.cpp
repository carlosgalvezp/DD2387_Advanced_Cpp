#include <characters/animal.h>

using namespace lab3::characters;

Animal::Animal()
{

}
Animal::Animal(const std::string &name, const std::string &type, Place* place)
    : Character(name,type, place)
{
    this->talk_msgs_ =
    {
        "Grrrr"
    };
}

Animal::~Animal()
{}

bool Animal::lookForFood()
{
    std::stringstream ss,ss2;
    ss << this->name() <<" is looking for food...";
    lab3::utils_io::print_newline(ss.str());

    double p_food = *this->currentPlace() == *this->natural_habitat_ ? PROB_FOOD_IN : PROB_FOOD_OUT;

    if(lab3::utils::eventHappens(p_food))
    {
        lab3::utils_io::print_newline("It found food!");
        this->add_life(LIFE_FOOD);
        return true;
    }
    lab3::utils_io::print_newline("It did not find food");
    return false;
}
