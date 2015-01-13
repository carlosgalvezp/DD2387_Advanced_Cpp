#include <characters/player.h>

using namespace lab3::characters;

Player::Player()
{}

Player::Player(const std::string &name, Place *place)
    : Human(name, TYPE_HUMAN, place),
      finished_game_(false),
      experience_(0),
      kills_wolf_(0),
      kills_vampire_(0),
      event_trained_(false),
      home_(place)
{
    // ** The player has 3 objects: backpack, protection and weapon
    this->objects_ = std::vector<Object*>(3, nullptr);

    // ** The player always starts with a small backpack
    this->objects_.at(0) = new objects::Container("small backpack",5,DEFAULT_BACKPACK_VOLUME,
                                                                     DEFAULT_BACKPACK_WEIGHT,
                                                                     DEFAULT_BACKPACK_MAX_WEIGHT,
                                                                     DEFAULT_BACKPACK_VOLUME);
    this->money_ = INITIAL_MONEY;
    // ** Initialize talk messages
    talk_msgs_ = {"Hi, I am "+name};

    // ** Include additional commands
}

Player::~Player()
{
}

lab3::objects::Container* Player::getBackpack() {return static_cast<lab3::objects::Container*>(this->objects_[0]);}
lab3::objects::Weapon*    Player::getWeapon()       const{return static_cast<lab3::objects::Weapon*>(this->objects_[1]);}
lab3::objects::Protection*Player::getProtection()   const{return static_cast<lab3::objects::Protection*>(this->objects_[2]);}

std::string Player::action(bool display_info)
{
    return lab3::input::read_player_input(this);
}

bool Player::pick_up(Object &object)
{
    // ** Check if it's a backpack
    objects::Container* back_ptr = dynamic_cast<objects::Container*>(&object);
    if(back_ptr != nullptr)
    {
        return pick_up_backpack(*back_ptr);
    }

    // ** Check if it's weapon
    else if(dynamic_cast<objects::Weapon*>(&object) != nullptr)
    {
        std::cout << "PICKING UP WEAPON"<<std::endl;
        if(this->getWeapon() != nullptr)
        {
            this->drop(*this->getWeapon());
        }
        this->currentPlace()->pick_up(object);
        this->objects_[1] = &object;
        lab3::utils_io::print_newline("You have picked up a "+object.name());
        return true;
    }

    // ** Check if it's protection
    else if(dynamic_cast<objects::Protection*>(&object) != nullptr)
    {
        if(this->getProtection() != nullptr)
        {
            this->drop(*this->getProtection());
        }
        this->currentPlace()->pick_up(object);
        this->objects_[2] = &object;
        lab3::utils_io::print_newline("You have picked up a "+object.name());
        return true;
    }

    // ** Otherwise just try to put it in the backpack
    else
    {
        objects::Container* backpack = this->getBackpack();
        if(backpack != nullptr)
        {
            // ** Check if we can put this object in the bag
            if(backpack->add(object))
            {
                lab3::utils_io::print_newline("You have picked up a "+object.name());
                return this->current_place_->pick_up(object);
            }
        }
        else
        {
            lab3::utils_io::print_newline("You don't have a backpack, so you cannot pick this object up! You better go and buy a new one");
            lab3::utils_io::wait_for_enter();
            return false;
        }
    }
    return false;
}

bool Player::pick_up_backpack(objects::Container &new_backpack)
{
    if(this->getBackpack() != nullptr) // I already have a backpack, so I need to exchange contents
    {
        objects::Container* backpack = this->getBackpack();

        // Try to move stuff from one backpack to the other one
        if(backpack->isMovableTo(new_backpack))
        {
            // Move items from old to new backpack
            backpack->moveObjectsTo(new_backpack);

            // Remove old backpack
            delete backpack;
        }
        else
        {
            return false;
        }
    }
    if(this->currentPlace()->pick_up(new_backpack))
    {
        // Update backpack
        lab3::utils_io::print_newline("You have picked up a "+new_backpack.name());
        this->objects_[0] = &new_backpack;
        return true;
    }
    return false;
}

bool Player::drop(Object &object)
{
    std::stringstream ss;
    // ** Check if it's any of the objects we already have
    for(Object* o : objects_)
    {
        if(*o == object)
        {
            o = nullptr;
            this->current_place_->drop(object);
            ss << "You have dropped a "<<object.name() << " in the " <<this->currentPlace()->name()<<".";
            lab3::utils_io::print_newline(ss.str());
            return true;
        }
    }

    // ** Check if it's inside the container
    objects::Container* bag = this->getBackpack();
    if(bag!=nullptr && bag->remove(object))
    {
        this->current_place_->drop(object);
        ss << "You have dropped a "<<object.name() << " in the " <<this->currentPlace()->name()<<".";
        lab3::utils_io::print_newline(ss.str());
        return true;

    }
    return false;
}

void Player::talk_to(Character *character)
{
    // ** I talk first
    std::string msg = "[Player] " + this->getTalkMessages()[0];
    lab3::utils_io::print_newline(msg);

    // Let the other talk
    character->talk_to(*this);
}

bool Player::fight(Character &character)
{
    bool finished = Character::fight(character);

    if(finished) // Increase experience and check if we have killed all the monsters
    {
        if(this->isAlive())                 // Won -> increase experience
        {
            ++this->experience_;
            check_event_trained(character);
            check_event_final_monster(character);
        }
        this->is_fighting_ = false;

    }
    return finished;
}

bool Player::use(Object &o)
{
    lab3::objects::Usable* item_ptr = static_cast<lab3::objects::Usable*>(&o);
    if(item_ptr->use(*this))
    {
        // Remove from backpack if it's single use
        if(item_ptr->isSingleUse())
        {
            this->getBackpack()->remove(o);
            // Delete object
            delete item_ptr;
        }
        return true;
    }
    return false;
}

std::string Player::type() const
{
    return TYPE_PLAYER;
}

bool Player::finishedGame() const   {   return this->finished_game_;    }

int Player::getStrength() const
{
    int strength = Character::getStrength();
    if(this->getWeapon() != nullptr)
    {
        strength += this->getWeapon()->attackPoints();
    }
    return strength;
}

int Player::getDefense()    const
{
    int defense = Character::getDefense();
    if(this->getProtection() != nullptr)
    {
        defense += this->getProtection()->defensePoints();
    }
    return defense;
}

void Player::status()       const
{
    lab3::utils_io::clearScreen();
    lab3::utils_io::print_newline("===== PLAYER STATUS =====");
    lab3::utils_io::print_newline("=========================");

    // ** Attributes
    lab3::utils_io::print_newline("----- Attributes -----");
    std::cout << "-Life: "          <<this->getLifePoints()     <<std::endl;
    std::cout << "-Money: "         <<this->getMoney()             <<std::endl;
    std::cout << "-Strength: "      <<this->getStrength()       <<std::endl;
    std::cout << "-Defense: "       <<this->getDefense()        <<std::endl;
    std::cout << "-Initiative: "    <<this->getInitiative()     <<std::endl;

    // ** Current place
    lab3::utils_io::print_newline("----- Location -----");
    lab3::utils_io::print_newline(this->currentPlace()->description());

    // ** Equipment and inventory
    lab3::utils_io::print_newline("----- Objects -----");
    for(Object *o : this->objects())
    {
        if(o != nullptr)
            std::cout << "-"<<o->name()<<" - "<<o->description()<<std::endl;
    }
}

std::vector<std::string> Player::getCommands()
{
    std::vector<std::string> cmds;

    // ** Get place commands
    if(this->isFighting())
    {
        cmds = {CMD_FIGHT, CMD_SCAPE};
    }
    else
    {
        cmds = this->currentPlace()->getCommands();
    }
    cmds.push_back(CMD_USE_ITEM);
    cmds.push_back(CMD_STATUS);
    cmds.push_back(CMD_EXIT_GAME);
    return cmds;
}

void Player::check_event_trained(const Character &character)
{
    if(!event_trained_)
    {
        if(character.type() == TYPE_WOLF)  // it's a wolf
            ++this->kills_wolf_;
        else if(character.type() == TYPE_VAMPIRE) // it's a vampire
            ++this->kills_vampire_;

        if(this->experience_ >= MIN_EXPERIENCE &&
           this->kills_vampire_ >= MIN_KILL_ANIMAL &&
           this->kills_wolf_  >= MIN_KILL_ANIMAL)
        {
            event_trained_ = true;
            throw std::runtime_error(EVENT_ENOUGH_TRAIN);
        }
    }
}

void Player::check_event_final_monster(const Character &character)
{
    if(character.type() == TYPE_FINAL_MONSTER && !character.isAlive())
    {
        throw std::runtime_error(EVENT_GAME_FINISHED);
    }
}

