#include <characters/player.h>

using namespace lab3::characters;

Player::Player()
{}

Player::Player(const std::string &name, Place *place)
    : Human(name, TYPE_PLAYER, place), finished_game_(false)
{
    // ** The player always starts with a small backpack
    this->objects_.push_back((Object*)new objects::Container("small backpack",5,DEFAULT_BACKPACK_VOLUME,
                                                                                DEFAULT_BACKPACK_WEIGHT,
                                                                                DEFAULT_BACKPACK_MAX_WEIGHT,
                                                                                DEFAULT_BACKPACK_VOLUME));
    // ** Initialize talk messages
    talk_msgs_ = {"Hi, I am "+name};

    // ** Include additional commands
    // Action commands
    this->commands_.insert(this->commands_.end()-1,"status");

    // Fight commands
    this->fight_commands_.insert(this->fight_commands_.end()-1, "use potion");
}

Player::~Player()
{
    // Delete the backpack!
    delete objects_[0];
}

bool Player::action()
{
    lab3::utils_io::print_newline("Player action [TO DO]");
    return lab3::input::read_player_input(this);
}

bool Player::pick_up(Object &object)
{
    // ** Get the backpack (the player always has it, and it's the first element)
    objects::Container* backpack = (objects::Container*)(this->objects_[0]);

    if(backpack != nullptr)
    {
        // ** Check if we can put this object in the bag
        return backpack->add(object);
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
    int n_msg = 0; // Make this dynamic! XXXXXX
    std::string msg = "[Player] " + this->getTalkMessages()[n_msg];
    lab3::utils_io::print_newline(msg);

    // Let the other talk
    character->talk_to(this);
}

bool Player::fight(Character &character)
{
    return Character::fight(character);
}

std::string Player::type() const
{
    return "Player";
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
    std::cout << "-Money: "         <<this->money()             <<std::endl;
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
        std::cout << "-"<<o->description()<<std::endl;
    }
}

std::vector<std::string> Player::getCommands()
{
    std::vector<std::string> cmds = this->commands_;

    // ** Commands when the player is at a store
    if(dynamic_cast<places::Shop*>(this->currentPlace()) != nullptr)
    {
        cmds.insert(cmds.end()-1, "buy");
        cmds.insert(cmds.end()-1, "sell");
    }
    return cmds;
}
