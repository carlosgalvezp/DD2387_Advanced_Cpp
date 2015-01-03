#include <characters/player.h>

using namespace lab3::characters;

Player::Player()
{}

Player::Player(const std::string &name)
    : Human(name, TYPE_PLAYER), rescued_princess(false)
{}

Player::~Player()
{

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


    if(rescued_princess || cmd == "exit game")
        return true;
    return false;
}

std::string Player::type() const
{
    return "Player";
}
