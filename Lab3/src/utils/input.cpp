#include <utils/input.h>

std::string lab3::input::read_input(const std::vector<std::string> &available_commands)
{
    std::stringstream ss;
    char c;
    bool correct_command(true);
    std::cout << "\r";
    display_commands(available_commands);
    do
    {
        system("stty raw");  // Avoid having to press Enter after each character
        c=getchar();

        if(c == '\t') // Tab completion     // Might as well use function pointers
        {
            if(ss.str().size() == 0)        // The player doesn't know what to do
            {
                display_commands(available_commands);
            }
            else
            {
                std::string s_found = tab_completion(ss.str(), available_commands);
                if(s_found != " ")
                    ss.str(s_found);
            }
        }
        else if(c == 127) // Backspace
        {
            std::string new_str = ss.str().substr(0, ss.str().size()-1);
            ss.str("");
            ss << new_str;
        }
        else if(c == '\r') // Enter
        {
            if(std::find(available_commands.begin(), available_commands.end(), ss.str()) == available_commands.end())
            {
                ss.str("");
                correct_command = false;
                lab3::utils_io::print_newline("Incorrect command, please try again");
            }
            else
                correct_command = true;
        }
        else
        {
            ss << c;
        }
        std::cout << "\r" << "                               "; // Remove garbage printed from backspace or enter
        std::cout << "\r" << ">> "<<ss.str();
    }
    while (c != '\r' || !correct_command);
    std::cout << "\r" << ">> "<<ss.str()<<std::endl;
    system("stty cooked");  // Restore original config
    return ss.str();
}

bool lab3::input::read_player_input(lab3::characters::Player *player)
{
    std::string cmd = lab3::input::read_input(player->getCommands());

    // ** Go -> get directions from place
    if(cmd == "go")
    {
        lab3::input::cmd_go(player);
    }

    else if(cmd == "pick up")
    {
        lab3::input::cmd_pick_up(player);
    }

    else if(cmd == "drop")
    {
        lab3::input::cmd_drop(player);
    }

    else if(cmd == "talk to")
    {
        lab3::input::cmd_talk(player);
    }

//    else if(cmd == "fight")
//    {
//        lab3::input::cmd_fight(player);
//    }
    else if(cmd == "status")
    {
        player->status();
    }

    else if(player->finishedGame() || cmd == "exit game")
        return true;

    return false;
}

std::string lab3::input::tab_completion(const std::string &tmp_str, const std::vector<std::string> &available_commands)
{
    int n_found = 0;
    std::string s_found = " ";
    std::stringstream ss;
    for(std::string s : available_commands)
    {
        if(s.substr(0,tmp_str.size()) == tmp_str) // Found
        {
            ++n_found;
            s_found = s;
            ss << "\r" << s << std::endl;
        }
    }
    if(n_found != 1)
    {
        std::cout << ss.str();
        s_found = " ";
    }

    return s_found;
}

void lab3::input::display_commands(const std::vector<std::string> &commands)
{
    lab3::utils_io::print_newline("--- Available commands ---");
    for(std::string s : commands)
        lab3::utils_io::print_newline(s);

}

void lab3::input::wait_for_enter()
{
    lab3::utils_io::print_newline("Press Enter to continue...");
    getchar();
}


// =============================================================================
// =============================================================================
bool lab3::input::cmd_go(lab3::characters::Player *player)
{
    const std::map<std::string, lab3::Place*> &directions = player->currentPlace()->directions();
    std::vector<std::string> go_commands;
    for(std::pair<std::string, lab3::Place*> p : directions)
    {
        go_commands.push_back(p.first);
    }
    lab3::utils_io::print_newline("Go where?");
    std::string go_cmd = lab3::input::read_input(go_commands);

    // ** Actually go
    if(!player->go(go_cmd))
    {
        lab3::utils_io::print_newline("You cannot go "+go_cmd);
        return false;
    }
    return true;
}

bool lab3::input::cmd_pick_up(lab3::characters::Player *player)
{
    if(player->currentPlace()->objects().size() == 0)
    {
        lab3::utils_io::print_newline("There are no objects to pick up here");
        return false;
    }

    std::map<std::string, lab3::Object*> command_map;
    std::vector<std::string> command_str;
    for(lab3::Object* o : player->currentPlace()->objects())
    {
        command_map.insert(std::make_pair(o->name(), o));
        command_str.push_back(o->name());
    }
    lab3::utils_io::print_newline("Pick up what?");
    std::string cmd = lab3::input::read_input(command_str);

    // ** Actually go
    lab3::Object *o = command_map.at(cmd);
    if(o != nullptr)
    {
        if(!player->pick_up(*o))
        {
            lab3::utils_io::print_newline("You cannot pick up "+cmd);
            return false;
        }
    }
    return false;
}

bool lab3::input::cmd_drop(lab3::characters::Player *player)
{
    if(player->objects().size() == 0)
    {
        lab3::utils_io::print_newline("You have no objects to drop here");
        return false;
    }
    std::map<std::string, lab3::Object*> command_map;
    std::vector<std::string> command_str;
    // ** Get objects
    for(lab3::Object* o : player->objects())
    {
        command_map.insert(std::make_pair(o->name(), o));
        command_str.push_back(o->name());
    }
    // ** Get object inside container
    lab3::objects::Container* bag = (lab3::objects::Container*)player->objects()[0];
    for(lab3::Object* o : bag->objects())
    {
        command_map.insert(std::make_pair(o->name(), o));
        command_str.push_back(o->name());
    }

    lab3::utils_io::print_newline("Drop what?");
    std::string cmd = lab3::input::read_input(command_str);

    // ** Actually go
    lab3::Object *o = command_map.at(cmd);
    if(o != nullptr)
    {
        player->drop(*o);
        return true;
    }
    return false;
}

bool lab3::input::cmd_talk(lab3::characters::Player *player)
{
    // ** Get other characters
    if(player->currentPlace()->characters().size() > 1) // The player will always be here
    {
        std::map<std::string, lab3::Character*> command_map;
        std::vector<std::string> command_str;
        // ** Get characters
        for(lab3::Character* o : player->currentPlace()->characters())
        {
            if(*o != *player)
            {
                command_map.insert(std::make_pair(o->name(), o));
                command_str.push_back(o->name());
            }
        }

        lab3::utils_io::print_newline("Talk to whom?");
        std::string cmd = lab3::input::read_input(command_str);

        // ** Actually talk
        lab3::Character *c = command_map.at(cmd);
        if(c != nullptr)
        {
            player->talk_to(c);
            return true;
        }
    }
    else
    {
        lab3::utils_io::print_newline("There are no other characters to talk to");
    }
    return false;
}
