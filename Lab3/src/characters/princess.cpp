#include <characters/princess.h>

using namespace lab3::characters;

Princess::Princess()
{}

Princess::Princess(const std::string &name, Place *place)
    : Human(name, TYPE_PRINCESS, place), hope_(0)
{
    this->talk_msgs_ =
    {
        "Please help me, I am trapped here!",
        "You need to defeat the final monster in order to free me!"
    };
}

Princess::~Princess()
{}

std::string Princess::action(bool display_info)
{
    lab3::utils_io::print_newline("[Princess::action] ");
    return EVENT_NULL;
}

void Princess::addHope(int hope)
{
    this->hope_ = std::min(this->hope_ + hope, HOPE_MAX);
}

int Princess::getHope() const   {return this->hope_;}

bool Princess::distractMonster(characters::FinalMonster &monster)   const
{
    std::stringstream ss;
    ss << this->name() << " is trying to distract "<<monster.name();
    lab3::utils_io::print_newline(ss.str());

    double p_distract = (double)this->hope_ / HOPE_MAX;
    if(lab3::utils::eventHappens(p_distract))
    {
        std::stringstream ss2;
        ss2 << "The "<<monster.name() << " has been distracted by the "<<this->name()<<"!";
        lab3::utils_io::print_newline(ss.str());

        monster.addDistraction(this->hope_);
        return true;
    }
    else
    {
        return false;
    }
}
