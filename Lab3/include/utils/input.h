#ifndef INPUT_H
#define INPUT_H

#include <utils/input.h>
#include <utils/utils_io.h>
#include <character.h>
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
namespace input
{


std::string read_input(const std::vector<std::string> &available_commands);
void display_commands(const std::vector<std::string> &commands);
std::string tab_completion(const std::string &tmp_str, const std::vector<std::string> &available_commands);
void wait_for_enter();


}
}


#endif // INPUT_H
