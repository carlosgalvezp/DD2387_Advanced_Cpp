#include <characters/wise_man.h>

using namespace lab3::characters;

Wise_Man::Wise_Man()
{}

Wise_Man::Wise_Man(const std::string &name, Place *place)
    : Human(name, TYPE_HUMAN, place)
{
    this->talk_msgs_ =
    {
        "The princess is trapped in the Kings Castle."
        "You need a good equipment in order to defeat the final monster."
        "You should train a bit in the forest in order to gain experience, strength and money."
        "When you are ready, you need to open the Kings Castle and defeat the monster. The last time"
        " I saw the key was in the Dark Cave, but you will need a good illumination to find it. Good luck!"
    };
}

Wise_Man::~Wise_Man()
{}

std::string Wise_Man::action()
{
    std::cout << "[Wise_Man::action] TO-DO" << std::endl;
    return EVENT_NULL;
}
