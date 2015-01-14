#include <characters/wise_man.h>

using namespace lab3::characters;

Wise_Man::Wise_Man(const std::string &name, Place *place)
    : Human(name, TYPE_HUMAN, place),
      will_tell_about_wizard_(false),
      knowledge_(0)
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

ActionResult Wise_Man::action(bool display_info)
{

    Character* player = this->currentPlace()->getCharacter(NAME_PLAYER);
    if(player != nullptr)
    {
        return talk_to(*player);
    }
    else
    {
        return this->read();
    }
    return EVENT_NULL;
}

ActionResult Wise_Man::talk_to(Character &c)
{
    Character::talk_to(c);

    if(will_tell_about_wizard_)
    {
        lab3::utils_io::wait_for_enter();
        will_tell_about_wizard_ = false;
        return ActionResult(true,EVENT_MENTIONED_WIZARD);
    }
    return true;
}

void Wise_Man::setTellAboutWizard(bool x)
{
    will_tell_about_wizard_ = x;
}

ActionResult Wise_Man::read()
{
    this->knowledge_ += WISE_MAN_READ_POINTS;
    std::stringstream ss;
    ss << "The "<<this->name() << " reads an ancient book. His knowledge is increased up to "<<this->knowledge_<<" points";
    lab3::utils_io::print_newline(ss.str());

    return true;
}

int Wise_Man::getKnowledgePoints()  const   { return this->knowledge_;}
