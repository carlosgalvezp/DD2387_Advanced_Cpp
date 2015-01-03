#include <characters/player.h>

using namespace lab3::characters;

Player::Player()
{}

Player::Player(const std::string &name, Place *place)
    : Human(name, TYPE_PLAYER, place), rescued_princess(false)
{
    // ** The player always starts with a small backpack
    this->objects_.push_back((Object*)new objects::Container("small backpack",5,DEFAULT_BACKPACK_VOLUME,
                                                                                DEFAULT_BACKPACK_WEIGHT,
                                                                                DEFAULT_BACKPACK_MAX_WEIGHT,
                                                                                DEFAULT_BACKPACK_VOLUME));
}

Player::~Player()
{
    // Delete the backpack!
    delete objects_[0];
}

bool Player::action()
{
    lab3::utils_io::print_newline("Player action [TO DO]");
    std::string cmd = lab3::input::read_input(this->getBasicCommands());

    // ** Go -> get directions from place
    if(cmd == "go")
    {
        const std::map<std::string, Place*> &directions = this->current_place_->directions();
        std::vector<std::string> go_commands;
        for(std::pair<std::string, Place*> p : directions)
        {
            go_commands.push_back(p.first);
        }
        lab3::utils_io::print_newline("Go where?");
        std::string go_cmd = lab3::input::read_input(go_commands);

        // ** Actually go
        if(!this->go(go_cmd))
            lab3::utils_io::print_newline("You cannot go "+go_cmd);
    }

    if(cmd == "pick up")
    {
        if(this->currentPlace()->objects().size() == 0)
        {
            lab3::utils_io::print_newline("There are no objects to pick up here");
            return false;
        }
        std::map<std::string, Object*> command_map;
        std::vector<std::string> command_str;
        for(Object* o : this->currentPlace()->objects())
        {
            command_map.insert(std::make_pair(o->name(), o));
            command_str.push_back(o->name());
        }
        lab3::utils_io::print_newline("Pick up what?");
        std::string cmd = lab3::input::read_input(command_str);

        // ** Actually go
        Object *o = command_map.at(cmd);
        if(o != nullptr)
        {
            if(!this->pick_up(*o))
                lab3::utils_io::print_newline("You cannot pick up "+cmd);
        }
    }


    if(rescued_princess || cmd == "exit game")
        return true;
    return false;
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

std::string Player::type() const
{
    return "Player";
}
