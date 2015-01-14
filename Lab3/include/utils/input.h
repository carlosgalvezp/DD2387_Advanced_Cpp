#ifndef INPUT_H
#define INPUT_H

#include <utils/input.h>
#include <utils/utils_io.h>
#include <character.h>
#include <characters/player.h>
#include <place.h>
#include <stdio.h>

#include <utils/utils_io.h>

#include <names.h>

// STL
#include <sstream>
#include <string>
#include <vector>
#include <utility>

#define CMD_BACK_TO_MAIN "back to main menu"

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
std::string read_input(const std::vector<std::string> &available_commands,
                       const std::vector<std::string> &descriptions);

ActionResult read_player_input(lab3::characters::Player* player);
void display_commands(const std::vector<std::string> &commands);
void display_commands(const std::vector<std::string> &commands, const std::vector<std::string>& description);
std::vector<std::string> tab_completion(const std::string &tmp_str, const std::vector<std::string> &available_commands);

// ** Player commands
ActionResult cmd_go         (lab3::characters::Player* player);
ActionResult cmd_pick_up    (lab3::characters::Player* player);
ActionResult cmd_drop       (lab3::characters::Player* player);
ActionResult cmd_talk       (lab3::characters::Player* player);
ActionResult cmd_fight      (lab3::characters::Player* player);
ActionResult cmd_status     (lab3::characters::Player* player);
ActionResult cmd_exit_game  (lab3::characters::Player* player);
ActionResult cmd_buy        (lab3::characters::Player* player);
ActionResult cmd_sell       (lab3::characters::Player* player);
ActionResult cmd_use_item   (lab3::characters::Player* player);
ActionResult cmd_scape      (lab3::characters::Player* player);
ActionResult cmd_cure       (lab3::characters::Player* player);
ActionResult cmd_rest       (lab3::characters::Player* player);
ActionResult cmd_repair     (lab3::characters::Player* player);

}
}


#endif // INPUT_H
