#include "game_engine.h"

using namespace lab3::utils;

namespace lab3
{

GameEngine::GameEngine()
    : is_finished_(false)
{
}

GameEngine::~GameEngine()
{
    // ** Destroy places
    for(std::size_t i = 0; i < this->places_.size(); ++i)
    {
        Place* p = this->places_[i];
        delete p;
    }

    // ** Destroy objects
    for(std::size_t i = 0; i < this->objects_.size(); ++i)
    {
        Object* o = this->objects_[i];
        delete o;
    }

    // ** Destroy characters
    for(std::size_t i = 0; i < this->characters_.size(); ++i)
    {
        Character* c = this->characters_[i];
        delete c;
    }
}

void GameEngine::initGame()
{
    // ** Display main menu and choose option
    int option  = mainMenu();

    switch(option)
    {
    case 0:             // New game
        newGame();
        break;

    case 1:             // Load game
        break;

    case 2:             // Save game
        break;

    case 3:
        is_finished_ = true;
        break;
    }
}
void GameEngine::newGame()
{
    // ** Create places
    this->places_.push_back(new places::Home());
    this->places_.push_back(new places::Enchanted_Forest());
    this->places_.push_back(new places::Kings_Castle());

    // ** Create characters
    this->characters_.push_back(new characters::Paladin);
    this->characters_.push_back(new characters::Princess);

    // ** Create objects
    this->objects_.push_back(new objects::Key);

    // ** Put characters and objects in the places
    Place* home = this->places_[0];
    Place* forest = this->places_[1];
    Place* castle = this->places_[2];

    home->enter(*this->characters_[0]);
    castle->enter(*this->characters_[1]);

    Object* key = this->objects_[0];
    castle->drop(*key);

    // ** Connect places
    Direction *d1 = new Direction(Movement::NORTH, forest);
    Direction *d2 = new Direction(Movement::EAST, castle);

    home->addDirection(d1);
    forest->addDirection(d2);
}

int GameEngine::mainMenu()
{
    // ** Create options
    std::vector<UI_Option> options;
    options.push_back(UI_Option("New game", 'n'));
//    options.push_back(UI_Option("Load game",'l'));
//    options.push_back(UI_Option("Save game",'s'));
    options.push_back(UI_Option("Quit",     'q'));

    // ** Display and choose option
    int option = -1;
    do
    {
        // ** Clear screen
        system("clear");

        lab3::utils::displaySelectionMenu(options);
        option = lab3::utils::readKeyboardInput(options);
    }
    while (option < 0);

    return option;
}



void GameEngine::run()
{
    while(!this->is_finished_)
    {
        // ** Execute own actions

        // ** Execute other actors' actions
    }

    std::cout << "Thanks for playing" << std::endl;
}

}
