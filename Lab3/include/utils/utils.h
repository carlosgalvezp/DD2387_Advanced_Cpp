#ifndef UTILS_H
#define UTILS_H

// STL
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>

// Own
#include <utils/ui_option.h>
namespace lab3
{
namespace utils
{

/**
 * @brief Displays the available options
 * @param options
 */
void displaySelectionMenu(const std::vector<UI_Option> &options);

/**
 * @brief Reads (blocking) a character from the keyboard and parses it, according
 *        to the available options
 * @param options The available options
 * @return The index of the selected option. -1 if no such option is available
 */
int readKeyboardInput(const std::vector<UI_Option> &options);
}

}


#endif // UTILS_H
