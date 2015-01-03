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
    // ** Set seed for rand
    srand(time(NULL));

    // ** Display main menu and choose option
    int option  = mainMenu();

    switch(option)
    {
    case 0:             // New game
        newGame();
        break;

    case 1:
        is_finished_ = true;
        break;
    }
}
void GameEngine::newGame()
{
    // ** Create places
    this->places_.push_back(new places::Home("Home"));
    this->places_.push_back(new places::Enchanted_Forest("Enchanted Forest"));
    this->places_.push_back(new places::Kings_Castle("Kings Castle"));

    Place* home   = this->places_[0];
    Place* forest = this->places_[1];
    Place* castle = this->places_[2];

    // ** Create characters
    this->characters_.push_back(new characters::Player("Adventurous Player",home));
    this->characters_.push_back(new characters::Princess("Trapped Princess",castle));

    // ** Create objects
    this->objects_.push_back(new objects::Item("key",1000,1,1));

    home->enter(*this->characters_[0]);
    castle->enter(*this->characters_[1]);

    Object* key = this->objects_[0];
    castle->drop(*key);

    // ** Connect places
    home->addDirection(DIRECTION_NORTH, forest);
    forest->addDirection(DIRECTION_EAST, castle);
    forest->addDirection(DIRECTION_SOUTH, home);
    castle->addDirection(DIRECTION_WEST, forest);
}

int GameEngine::mainMenu()
{
    // ** Create options
    std::vector<UI_Option> options;
    options.push_back(UI_Option("New game", 'n'));
    options.push_back(UI_Option("Quit",     'q'));

    // ** Display and choose option
    int option = -1;
    do
    {
        // ** Clear screen
        lab3::utils_io::clearScreen();

        // ** Display menu
        lab3::utils::displaySelectionMenu(options);
        option = lab3::utils::readKeyboardInput(options);
    }
    while (option < 0);

    return option;
}



void GameEngine::run()
{
    lab3::utils_io::clearScreen();

    while(!this->is_finished_)
    {
        // ** Sort by initiative
        std::sort(characters_.begin(), characters_.end(),
                  [](Character* char1, Character* char2)
                  {return char1->getInitiative() > char2->getInitiative();});

        // ** Run actions
        for(Character *c : characters_)
        {
            bool finished = c->action();
            if (finished && c->type() == TYPE_PLAYER)
            {
                is_finished_ = true;
                break;
            }
            input::wait_for_enter();
        }

        // ** Remove dead characters
        std::vector<Character*> tmp;
        for(Character* c : characters_)
        {
            if (!c->isAlive())
            {
                delete c;
                continue;
            }
            tmp.push_back(c);
        }
        characters_ = tmp;
    }
    lab3::utils_io::print_newline("Thanks for playing!");
}

}
