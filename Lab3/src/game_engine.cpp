#include "game_engine.h"

using namespace lab3;

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
    Place* home         = new places::House("Home", true);
    Place* old_house    = new places::House("Old House", false);
    Place* hospital     = new places::Hospital("Hospital");
    Place* food_shop    = new places::Food_Shop("Food Shop", true);
    Place* armory       = new places::Armory("Armory",true);
    Place* forest       = new places::Forest("Enchanted Forest");
    Place* castle       = new places::Castle("Kings Castle", false);
    Place* cave         = new places::Cave("Dark Cave");

    this->places_.push_back(home);
    this->places_.push_back(old_house);
    this->places_.push_back(hospital);
    this->places_.push_back(forest);
    this->places_.push_back(castle);
    this->places_.push_back(food_shop);
    this->places_.push_back(armory);
    this->places_.push_back(cave);


    // ** Create main characters
    this->characters_.push_back(new characters::Player("Brave Player",home));
    this->characters_.push_back(new characters::Princess("Trapped Princess",castle));
    this->characters_.push_back(new characters::Wise_Man("Wise Man",old_house));
    this->characters_.push_back(new characters::FinalMonster("Powerful Final Monster", castle));


    // ** Create random animals in forest and cave
    std::vector<Place*> animal_places = {forest, cave};
    this->createAnimals(this->characters_, animal_places);

    // ** Create random objects
    std::vector<Place*> object_places = {food_shop, armory, forest, cave};
    this->createObjects(this->objects_, object_places);

    // ** Connect places
    lab3::places::connectPlaces(*home, *forest, DIRECTION_NORTH);
    lab3::places::connectPlaces(*home, *food_shop, DIRECTION_EAST);
    lab3::places::connectPlaces(*home, *armory, DIRECTION_WEST);
    lab3::places::connectPlaces(*home, *hospital, DIRECTION_SOUTH);
    lab3::places::connectPlaces(*forest, *castle, DIRECTION_EAST);

    std::cout << "END INIT" << std::endl;
    lab3::utils_io::wait_for_enter();
}

int GameEngine::mainMenu()
{
    // ** Create options
    std::vector<std::string> menu_options = {"new game", "quit"};

    // ** Display and choose option
    int option = -1;
    do
    {
        // ** Clear screen
        lab3::utils_io::clearScreen();

        // ** Display menu
        std::string s = lab3::input::read_input(menu_options);
        auto it = std::find(menu_options.begin(), menu_options.end(), s);
        if(it != menu_options.end())
        {
            option = it - menu_options.begin();
        }
    }
    while (option < 0);

    return option;
}



void GameEngine::run()
{
    lab3::utils_io::clearScreen();
    int round(1);
    while(!this->is_finished_)
    {
        lab3::utils_io::clearScreen();
        std::cout << "Round "<<round++<<std::endl;
        // ** Sort by initiative
        std::sort(characters_.begin(), characters_.end(),
                  [](Character* char1, Character* char2)
                  {return char1->getInitiative() > char2->getInitiative();});

        // ** Run actions
        for(Character *c : characters_)
        {
            if(c!= nullptr && c->isAlive())
            {
                bool finished = c->action();
                if (finished && c->type() == TYPE_PLAYER)
                {
                    is_finished_ = true;
                    break;
                }
                lab3::utils_io::wait_for_enter();
            }
        }

        // ** Remove dead characters
        std::vector<Character*> tmp;
        for(Character* c : characters_)
        {
            if (!c->isAlive())
            {
                // Remove from place
                c->currentPlace()->leave(*c);
                delete c;
                c = nullptr;
                continue;
            }
            tmp.push_back(c);
        }
        characters_ = tmp;
    }
    lab3::utils_io::print_newline("Thanks for playing!");
}

void GameEngine::createAnimals(std::vector<Character *> &characters,
                               std::vector<Place *> &animalPlaces)
{

}

void GameEngine::createObjects(std::vector<Object*> &objects,
                               std::vector<Place *> &objectPlaces)
{
    for(Place *p : objectPlaces)
    {
        std::cout << "Starting place "<<p->name()<<std::endl;
        p->generateObjects();
        const std::vector<Object*> &objs = p->objects();
        std::cout << "Objects: "<<objs.size()<<std::endl;

        for(Object *o : objs)
            objects.push_back(o);
    }
    std::cout << "END OBJECTS"<< std::endl;
}
