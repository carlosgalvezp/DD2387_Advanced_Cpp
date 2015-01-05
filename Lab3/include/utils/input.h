#ifndef INPUT_H
#define INPUT_H

#include <utils/input.h>
#include <utils/utils_io.h>
#include <character.h>
#include <characters/player.h>
#include <place.h>
#include <stdio.h>

#include <utils/utils_io.h>

// STL
#include <sstream>
#include <string>
#include <vector>
#include <utility>

namespace lab3
{
namespace characters    // Forward declaration
{
class Player;
}
}

namespace lab3
{
namespace input
{

std::string read_input(const std::vector<std::string> &available_commands);
bool read_player_input(lab3::characters::Player* player);
void display_commands(const std::vector<std::string> &commands);
std::string tab_completion(const std::string &tmp_str, const std::vector<std::string> &available_commands);

// ** Player commands
bool cmd_go         (lab3::characters::Player* player);
bool cmd_pick_up    (lab3::characters::Player* player);
bool cmd_drop       (lab3::characters::Player* player);
bool cmd_talk       (lab3::characters::Player* player);
bool cmd_fight      (lab3::characters::Player* player);
bool cmd_status     (lab3::characters::Player* player);
bool cmd_exit_game  (lab3::characters::Player *player);
bool cmd_buy        (lab3::characters::Player* player);

}
}


#endif // INPUT_H
