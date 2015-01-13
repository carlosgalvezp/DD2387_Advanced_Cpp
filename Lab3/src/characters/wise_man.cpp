#include <characters/wise_man.h>

using namespace lab3::characters;

Wise_Man::Wise_Man()
{}

Wise_Man::Wise_Man(const std::string &name, Place *place)
    : Human(name, TYPE_HUMAN, place),
      will_tell_about_wizard_(false)
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

std::string Wise_Man::action(bool display_info)
{
    try
    {
        if(this->currentPlace()->characters().size() != 0)
        {
            // Only talk to player
            for(Character* c : this->currentPlace()->characters())
            {
                if(c->type() == TYPE_PLAYER)
                {
                    talk_to(*c);
                    break;
                }
            }
        }
    }
    catch (std::runtime_error &e)   {return e.what();}
    return EVENT_NULL;
}

void Wise_Man::talk_to(Character &c)
{
    Character::talk_to(c);

    if(will_tell_about_wizard_)
    {
        throw std::runtime_error(EVENT_MENTIONED_WIZARD);
    }
}

void Wise_Man::setTellAboutWizard(bool x)
{
    will_tell_about_wizard_ = x;
}

void Wise_Man::read()
{
    this->knowledge_ += WISE_MAN_READ_POINTS;
    std::stringstream ss;
    ss << "The "<<this->name() << " reads an ancient book. His knowledge is increased up to "<<this->knowledge_<<" points";
    lab3::utils_io::print_newline(ss.str());
}

int Wise_Man::getKnowledgePoints()  const   { return this->knowledge_;}
