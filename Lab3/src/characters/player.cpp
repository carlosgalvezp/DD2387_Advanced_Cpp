#include <characters/player.h>

using namespace lab3::characters;

Player::Player()
{}

Player::Player(const std::string &name, Place *place)
    : Human(name, TYPE_PLAYER, place),
      finished_game_(false),
      experience_(0),
      kills_wolf_(0),
      kills_vampire_(0),
      event_trained_(false),
      home_(place)
{
    // ** The player always starts with a small backpack
    this->objects_.push_back((Object*)new objects::Container("small backpack",5,DEFAULT_BACKPACK_VOLUME,
                                                                                DEFAULT_BACKPACK_WEIGHT,
                                                                                DEFAULT_BACKPACK_MAX_WEIGHT,
                                                                                DEFAULT_BACKPACK_VOLUME));
    this->money_ = INITIAL_MONEY;
    // ** Initialize talk messages
    talk_msgs_ = {"Hi, I am "+name};

    // ** Include additional commands
    // Action commands
    this->commands_.insert(this->commands_.end()-1,"use item");
    this->commands_.insert(this->commands_.end()-1,"status");
}

Player::~Player()
{
}

lab3::objects::Container* Player::getBackpack(){return static_cast<lab3::objects::Container*>(this->objects_[0]);}

std::string Player::action(bool display_info)
{
    return lab3::input::read_player_input(this);
}

bool Player::pick_up(Object &object)
{
    // ** Get the backpack (the player always has it, and it's the first element)
    objects::Container* backpack = (objects::Container*)(this->objects_[0]);

    // ** Check if it's an item (put it in the backpack)
    if(dynamic_cast<lab3::objects::Usable*>(&object) != nullptr)
    {
        if(backpack != nullptr)
        {
            // ** Check if we can put this object in the bag
            if(backpack->add(object))
            {
                this->current_place_->pick_up(object);
                return true;
            }
        }
    }
    else
    {
        // ** Check if it's backpack
        objects::Container* back_ptr = dynamic_cast<objects::Container*>(&object);
        if(back_ptr != nullptr)
        {
            // Try to move stuff from one backpack to the other one
            if(backpack->isMovableTo(*back_ptr))
            {
                // Pick new backpack
                this->current_place_->pick_up(object);
                lab3::utils_io::print_newline("You have picked up a "+object.name());

                // Move items from old to new backpack
                backpack->moveObjectsTo(*back_ptr);

                // Remove old backpack
                delete backpack;

                // Update backpack
                this->objects_[0] = back_ptr;
                return true;
            }
        }
    }
    return false;
}

bool Player::drop(Object &object)
{
    std::stringstream ss;
    // ** Check if it's any of the objects we already have
    for(auto it = this->objects_.begin(); it < this->objects_.end(); ++it)
    {
        if(**it == object)
        {
            this->objects_.erase(it);
            this->current_place_->drop(object);
            ss << "You have dropped a "<<object.name() << " in the " <<this->currentPlace()<<".";
            lab3::utils_io::print_newline(ss.str());
            return true;
        }
    }

    // ** Check if it's inside the container
    objects::Container* bag = (objects::Container*)(this->objects_[0]);
    if(bag->remove(object))
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
        std::cout << "-"<<o->name()<<" - "<<o->description()<<std::endl;
    }
}

std::vector<std::string> Player::getCommands()
{
    std::vector<std::string> cmds = this->commands_;

    // ** Commands when the player is at a store
    if(dynamic_cast<places::Shop*>(this->currentPlace()) != nullptr)
    {
        cmds = {"go","buy","exit game"};
    }

    // ** Commands when the player is fighting
    if(this->isFighting())
    {
        cmds = {"fight","scape","use item","exit game"};
    }
    return cmds;
}

void Player::check_event_trained(const Character &character)
{
    if(character.type() == TYPE_WOLF)  // it's a wolf
        ++this->kills_wolf_;
    else if(character.type() == TYPE_VAMPIRE) // it's a vampire
        ++this->kills_vampire_;

    if(this->experience_ >= MIN_EXPERIENCE &&
       this->kills_vampire_ >= MIN_KILL_ANIMAL &&
       this->kills_wolf_  >= MIN_KILL_ANIMAL)
    {
        throw std::runtime_error(EVENT_ENOUGH_TRAIN);
    }
}

void Player::check_event_final_monster(const Character &character)
{
    if(character.type() == TYPE_FINAL_MONSTER && !character.isAlive())
    {
        throw std::runtime_error(EVENT_GAME_FINISHED);
    }
}
