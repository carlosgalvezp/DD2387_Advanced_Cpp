#include <characters/princess.h>

using namespace lab3::characters;

Princess::Princess()
{}

Princess::Princess(const std::string &name, Place *place)
    : Human(name, TYPE_HUMAN, place), hope_(0)
{


    this->action_commands_ = {CMD_TALK, CMD_DISTRACT_MONSTER};
}

Princess::~Princess()
{}

ActionResult Princess::action(bool display_info)
{
    Character *player = this->currentPlace()->getCharacter(NAME_PLAYER);
    Character *monster = this->currentPlace()->getCharacter(NAME_FINAL_MONSTER);
    if(player == nullptr)   // The player is not here
    {
        this->talk_msgs_ =
        {
            "Let me out, please!",
            "Someone will come and save me, I can tell you!",
            "You will get destroyed soon!"
        };
        // Just beg the monster for liberation
        talk_to(*monster);
    }
    else
    {
        // Try to help the player by giving advice or distracting the monster
        this->talk_msgs_ =
        {
            "Attack this monster! I will try to distract him meanwhile!",
            "Remember to use potions when you are low on life points!"
        };

        if(monster->getDefense() == 0)
        {
            talk_msgs_.push_back("Its thick skin has been weakened a lot!! Now it's the perfect time to destroy the "+monster->name()+"!!");
        }
        else
        {
            talk_msgs_.push_back("His skin is too thick for a normal weapon. Some kind of magic is required to remove that protection!");
        }

        std::vector<int> command_points = {5,this->hope_};
        std::string cmd = lab3::utils::getRandomCommandPoints(this->action_commands_, command_points);
        if(cmd == CMD_TALK)
        {
            talk_to(*this->currentPlace()->getCharacter(NAME_PLAYER));
        }
        else if(cmd == CMD_DISTRACT_MONSTER)
        {
            this->distractMonster(*static_cast<characters::FinalMonster*>(monster));
        }

        this->addHope(1); // The hope increases when she sees the Player
        std::stringstream ss;
        ss << "The "<<this->name()<<" increases her hope up to " << this->hope_<<" when seeing the "<<player->name()<<" <3";
        lab3::utils_io::print_newline(ss.str());
    }

    return EVENT_NULL;
}

void Princess::addHope(int hope)
{
    this->hope_ = std::min(this->hope_ + hope, HOPE_MAX);
}

int Princess::getHope() const   {return this->hope_;}

ActionResult Princess::distractMonster(characters::FinalMonster &monster)   const
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
