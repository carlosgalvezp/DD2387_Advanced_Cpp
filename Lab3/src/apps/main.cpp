// STL
#include <iostream>
#include <vector>

// Own
#include <game_engine.h>
#include <utils/utils.h>
//#include <utils/ui_option.h>


using namespace lab3::utils;

int mainMenu();
void mainMenuOptions(std::vector<UI_Option> &options);
void run(const lab3::GameEngine &game_engine, int option);


int main()
{
    system("clear"); // Clear screen

    // ** Create Game Engine
    lab3::GameEngine game_engine;

    // ** Display Main Menu and select option
    int option = mainMenu();

    // ** Run the game
    run(game_engine, option);

    // ** Finish game
    std::cout << "======= THE END ======="<<std::endl;
    return 0;
}

// =============================================================================
int mainMenu()
{
    // ** Create options
    std::vector<UI_Option> options;
    mainMenuOptions(options);

    // ** Display and choose option
    int option = -1;
    do
    {
        std::cout << "Please select an option" << std::endl;
        lab3::utils::displaySelectionMenu(options);
        option = lab3::utils::readKeyboardInput(options);
    }
    while (option < 0);

    return option;
}

void mainMenuOptions(std::vector<UI_Option> &options)
{
    options.clear();
    options.push_back(UI_Option("New game", 'n'));
    options.push_back(UI_Option("Load game",'l'));
    options.push_back(UI_Option("Save game",'s'));
    options.push_back(UI_Option("Quit",     'q'));
}

void run(const lab3::GameEngine &game_engine, int option)
{
    // ** Run game
    switch(option)
    {
    case 0:
        break;

    case 1:
        break;

    case 2:
        break;
    case 3:
        break;
    }
}
