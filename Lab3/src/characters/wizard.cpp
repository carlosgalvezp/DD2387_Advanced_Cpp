#include <characters/wizard.h>

using namespace lab3::characters;

Wizard::Wizard(const std::string &name, Place *place, std::map<std::string, Place *> &world_places)
    : Human(name, TYPE_WIZARD, place),
      talked_to_player_(false),
      magic_points_(50),
      world_places_(world_places)

{
    this->talk_msgs_ = {"I am the "+name+". I only appear in crucial moments, and only the right person can see me "
                        "The Princess needs to be saved, for which the monster inside the King's Castle needs to be killed... "
                        "However, there is no weapon in the world that can break through its thick skin. Some magic is needed "
                        "in order to weaken it. I will come with you and together we will destroy the monster"};
}

Wizard::~Wizard()
{}

int Wizard::getMagicPoints()    const   {return this->magic_points_;}

ActionResult Wizard::action(bool display_info)
{
    if(magic_points_ > 40)
    {
        if(this->currentPlace()->name() == NAME_CASTLE && this->currentPlace()->containsCharacter(NAME_PLAYER))
        {
            Character* monster = this->currentPlace()->getCharacter(NAME_FINAL_MONSTER);
            monster->add_defense(-monster->getDefense());
            std::stringstream ss;
            ss<< "The "<<this->name()<<" uses a powerful magic which totally destroys the "<<monster->name()
                 <<" defense. Now it is easier to fight with! ";
            lab3::utils_io::print_newline(ss.str());
            magic_points_ = 0;
        }
    }
    else
    {
        std::stringstream ss;
        ss << "The "<<this->name()<< " recently used a powerful magic, so now he needs to recover"<<std::endl;
        this->recover_magic();
    }
    return EVENT_NULL;
}

ActionResult Wizard::talk_to(Character &character)
{
    Character::talk_to(character);

    if(character.type() == TYPE_PLAYER && this->currentPlace()->name() != NAME_CASTLE) // The wizard will be moved to the Castle
    {
        this->teleport(*this->world_places_.at(NAME_CASTLE));
    }
    return true;
}

ActionResult Wizard::teleport(Place &place)
{
    std::stringstream ss;
    ss << "The "<<NAME_WIZARD<<" teleports to "<<place.name();
    lab3::utils_io::print_newline(ss.str());
    return place.enter(*this);
}

void Wizard::recover_magic()
{
    std::stringstream ss;
    this->magic_points_ = std::min(this->magic_points_ + WIZARD_RECOVER_MAGIC_POINTS, WIZARD_MAX_MAGIC_POINTS);
    ss << "The "<<this->name()<<" recovers magic up to "<<this->magic_points_<<" points";

    lab3::utils_io::print_newline(ss.str());
}
