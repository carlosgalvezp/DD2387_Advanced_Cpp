#include <utils/input.h>

typedef bool(*CmdFunction)(lab3::characters::Player*);
std::map<std::string, CmdFunction> cmd_map =
{
    {CMD_DROP  ,    &lab3::input::cmd_drop},
    {CMD_FIGHT,     &lab3::input::cmd_fight},
    {CMD_GO,        &lab3::input::cmd_go},
    {CMD_PICK_UP,   &lab3::input::cmd_pick_up},
    {CMD_TALK,      &lab3::input::cmd_talk},
    {CMD_STATUS,    &lab3::input::cmd_status},
    {CMD_USE_ITEM,  &lab3::input::cmd_use_item},
    {CMD_EXIT_GAME, &lab3::input::cmd_exit_game},
    {CMD_BUY,       &lab3::input::cmd_buy},
    {CMD_SCAPE,     &lab3::input::cmd_scape},
    {CMD_REST,      &lab3::input::cmd_rest},
    {CMD_CURE,      &lab3::input::cmd_cure},
    {CMD_REPAIR,    &lab3::input::cmd_repair}
};

std::string lab3::input::read_input(const std::vector<std::string> &available_commands)
{
    return read_input(available_commands, std::vector<std::string>());
}

std::string lab3::input::read_input(const std::vector<std::string> &available_commands,
                                    const std::vector<std::string> &descriptions)
{
    std::stringstream ss;
    char c;
    bool correct_command(true);
    std::cout << "\r";
    display_commands(available_commands, descriptions);
    do
    {
        system("stty raw");  // Avoid having to press Enter after each character
        c=getchar();

        if(c == '\t') // Tab completion     // Might as well use function pointers
        {
            if(ss.str().size() == 0)        // The player doesn't know what to do
            {
                display_commands(available_commands, descriptions);
            }
            else
            {
                std::vector<std::string> findings = tab_completion(ss.str(), available_commands);
                if(findings.size() == 0)
                {
                    ss.str(" ");
                }
                else if(findings.size() == 1)
                {
                    ss.str("");
                    ss<< findings[0];
                }
                else
                {
                    ss.str("");
                    ss << lab3::utils::commonString(findings);
                    display_commands(findings);
                }
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

std::string lab3::input::read_player_input(lab3::characters::Player *player)
{
    // ** Update commands depending on the current place
    bool success(false);
    do
    {
        lab3::utils_io::clearScreen();
        std::string cmd = lab3::input::read_input(player->getCommands());
        if(cmd_map.find(cmd) != cmd_map.end())
        {
            try
            {
                 success = (*cmd_map.at(cmd))(player); // Using a map of function pointers with key = cmd
            }
            catch(std::exception &e)   // Events are thrown as exceptions
            {
                return e.what();
            }

            if(!success) lab3::utils_io::wait_for_enter();
        }
        if(player->finishedGame())
        {
            return EVENT_GAME_FINISHED;
        }
        else if(cmd == CMD_EXIT_GAME)
        {
            return EVENT_QUIT_GAME;
        }
    }while(!success);

    return EVENT_NULL;
}

std::vector<std::string> lab3::input::tab_completion(const std::string &tmp_str, const std::vector<std::string> &available_commands)
{
    std::vector<std::string> findings;
    for(std::string s : available_commands)
    {
        if(s.substr(0,tmp_str.size()) == tmp_str) // Found
        {
            findings.push_back(s);
        }
    }
    return findings;
}

void lab3::input::display_commands(const std::vector<std::string> &commands)
{
    return display_commands(commands, std::vector<std::string>());
}

void lab3::input::display_commands(const std::vector<std::string> &commands,
                                   const std::vector<std::string> &description)
{
    lab3::utils_io::clearScreen();
    lab3::utils_io::print_newline("--- Available commands ---\n");
    for(std::size_t i = 0; i < commands.size(); ++i)
    {
        std::string s  = commands[i];
        if(description.size() == commands.size())
        {
            if(description[i].size() != 0)
                s = commands[i] + " ["+description[i]+"]";
        }
        lab3::utils_io::print_newline(s);
    }
    lab3::utils_io::print_newline("\n>> Type to select the command, use tab-completion. Case-sensitive");
}



// =============================================================================
// =============================================================================
bool lab3::input::cmd_go(lab3::characters::Player *player)
{
    const std::map<std::string, lab3::Place*> &directions = player->currentPlace()->directions();
    std::vector<std::string> command_str;
    std::vector<std::string> command_desc;
    for(std::pair<std::string, lab3::Place*> p : directions)
    {
        command_str.push_back(p.first);
        command_desc.push_back("To " + p.second->name());
    }
    command_str.push_back(CMD_BACK_TO_MAIN);
    command_desc.push_back("");
    lab3::utils_io::print_newline("Go where?");
    std::string cmd = lab3::input::read_input(command_str, command_desc);

    if(cmd == CMD_BACK_TO_MAIN){
        lab3::utils_io::print_newline("Going back to main menu...");
        return false;
    }

    // ** Actually go
    if(!player->go(cmd))
    {
        lab3::utils_io::print_newline("You cannot go "+cmd);
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
    std::vector<std::string> command_desc;

    for(lab3::Object* o : player->currentPlace()->objects())
    {
        command_map.insert(std::make_pair(o->name(), o));
        command_str.push_back(o->name());
        command_desc.push_back(o->description());
    }
    command_str.push_back(CMD_BACK_TO_MAIN);
    command_desc.push_back("");

    lab3::utils_io::print_newline("Pick up what?");
    std::string cmd = lab3::input::read_input(command_str, command_desc);

    if(cmd == CMD_BACK_TO_MAIN){
        lab3::utils_io::print_newline("Going back to main menu...");
        return false;
    }
    // ** Actually pick object
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
    std::vector<std::string> command_desc;

    // ** Get objects
    for(lab3::Object* o : player->objects())
    {
        command_map.insert(std::make_pair(o->name(), o));
        command_str.push_back(o->name());
        command_desc.push_back(o->description());
    }
    // ** Get object inside container
    lab3::objects::Container* bag = (lab3::objects::Container*)player->objects()[0];
    for(lab3::Object* o : bag->objects())
    {
        command_map.insert(std::make_pair(o->name(), o));
        command_str.push_back(o->name());
        command_desc.push_back(o->description());
    }

    command_str.push_back(CMD_BACK_TO_MAIN);
    command_desc.push_back("");

    lab3::utils_io::print_newline("Drop what?");
    std::string cmd = lab3::input::read_input(command_str);

    if(cmd == CMD_BACK_TO_MAIN){
        lab3::utils_io::print_newline("Going back to main menu...");
        return false;
    }
    // ** Actually drop
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
        command_str.push_back(CMD_BACK_TO_MAIN);

        lab3::utils_io::print_newline("Talk to whom?");
        std::string cmd = lab3::input::read_input(command_str);

        if(cmd == CMD_BACK_TO_MAIN){
            lab3::utils_io::print_newline("Going back to main menu...");
            return false;
        }
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

bool lab3::input::cmd_fight(lab3::characters::Player *player)
{
    // ** Check if already fighting
    if(player->isFighting())
    {
        player->fight(*player->fighter());
        return true;
    }
    // ** Get other characters
    if(player->currentPlace()->characters().size() > 1) // There are other characters appart from myself
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
        command_str.push_back(CMD_BACK_TO_MAIN);

        lab3::utils_io::print_newline("Fight with whom?");
        std::string cmd = lab3::input::read_input(command_str);

        if(cmd == CMD_BACK_TO_MAIN){
            lab3::utils_io::print_newline("Going back to main menu...");
            return false;
        }
        // ** Actually fight
        lab3::Character *c = command_map.at(cmd);
        if(c != nullptr)
        {
            player->fight(*c);
            return true;
        }
    }
    else
    {
        lab3::utils_io::print_newline("There are no other characters to fight with");
    }
    return false;
}

bool lab3::input::cmd_status(lab3::characters::Player *player)
{
    player->status();
    return false;
}

bool lab3::input::cmd_exit_game(lab3::characters::Player *player)
{
    lab3::utils_io::print_newline("Exiting game...");
    return true;
}

bool lab3::input::cmd_buy(lab3::characters::Player *player)
{
    // ** Get objects in the store
    if(player->currentPlace()->objects().size() == 0)
    {
        lab3::utils_io::print_newline("There is nothing to buy here");
        return false;
    }
    std::map<std::string, lab3::Object*> command_map;
    std::vector<std::string> command_str;
    std::vector<std::string> command_desc;

    // ** Get objects
    for(lab3::Object* o : player->currentPlace()->objects())
    {
        command_map.insert(std::make_pair(o->name(), o));
        // Don't show duplicates
        if(std::find(command_str.begin(), command_str.end(), o->name()) == command_str.end())
        {
            command_str.push_back(o->name());
            command_desc.push_back(o->description());
        }
    }

    command_str.push_back(CMD_BACK_TO_MAIN);
    command_desc.push_back("");

    lab3::utils_io::print_newline("Buy what?");
    std::string cmd = lab3::input::read_input(command_str, command_desc);

    if(cmd == CMD_BACK_TO_MAIN){
        lab3::utils_io::print_newline("Going back to main menu...");
        return false;
    }
    // ** Actually buy
    lab3::Object *o = command_map.at(cmd);
    if(o != nullptr)
    {
        return player->buy(*o);
    }
    return false;
}

//bool lab3::input::cmd_sell(lab3::characters::Player *player)
//{
//    // ** Get objects the player has
//    if(player->objects().size() == 0)
//    {
//        lab3::utils_io::print_newline("You have no objects to sell!");
//        return false;
//    }
//    std::map<std::string, lab3::Object*> command_map;
//    std::vector<std::string> command_str;
//    std::vector<std::string> command_desc;

//    // ** Get objects
//    for(lab3::Object* o : player->objects())
//    {
//        command_map.insert(std::make_pair(o->name(), o));
//        command_str.push_back(o->name());
//        command_desc.push_back(o->description());
//    }

//    command_str.push_back(CMD_BACK_TO_MAIN);
//    command_desc.push_back("");

//    lab3::utils_io::print_newline("Sell what?");
//    std::string cmd = lab3::input::read_input(command_str);

//    if(cmd == CMD_BACK_TO_MAIN){
//        lab3::utils_io::print_newline("Going back to main menu...");
//        return false;
//    }
//    // ** Actually buy
//    lab3::Object *o = command_map.at(cmd);
//    if(o != nullptr)
//    {
//        return player->sell(*o);
//    }
//    return false;
//}

bool lab3::input::cmd_use_item(lab3::characters::Player *player)
{
    // ** Get objects in the backpack
    if(player->getBackpack()->objects().size() == 0)
    {
        lab3::utils_io::print_newline("The backpack is empty!");
        return false;
    }
    std::map<std::string, lab3::objects::Usable*> command_map;
    std::vector<std::string> command_str;
    std::vector<std::string> command_desc;

    // ** Get objects
    for(lab3::Object* o : player->getBackpack()->objects())
    {
        command_map.insert(std::make_pair(o->name(), static_cast<lab3::objects::Usable*>(o)));
        command_str.push_back(o->name());
        command_desc.push_back(o->description());
    }

    command_str.push_back(CMD_BACK_TO_MAIN);
    command_desc.push_back("");

    lab3::utils_io::print_newline("Use what?");
    std::string cmd = lab3::input::read_input(command_str);

    if(cmd == CMD_BACK_TO_MAIN)
    {
        lab3::utils_io::print_newline("Going back to main menu...");
        return false;
    }
    // ** Actually use it
    lab3::objects::Usable *o = command_map.at(cmd);
    if(o != nullptr)
    {
        return player->use(*o);
    }
    return false;
}

bool lab3::input::cmd_scape(lab3::characters::Player *player)
{
    player->scape();
    return true;
}

bool lab3::input::cmd_rest(lab3::characters::Player *player)
{
    // Only available at home
    lab3::places::Home* home = static_cast<lab3::places::Home*>(player->currentPlace());
    return home->rest(*player);
}

bool lab3::input::cmd_cure(lab3::characters::Player *player)
{
    // Only available at hospital
    lab3::places::Hospital* hospital = static_cast<lab3::places::Hospital*>(player->currentPlace());
    return hospital->cure(*player);
}

bool lab3::input::cmd_repair(lab3::characters::Player *player)
{
    // Only available at armory
    lab3::places::Armory* armory = static_cast<lab3::places::Armory*>(player->currentPlace());
    return armory->repairEquipment(*player);
}


