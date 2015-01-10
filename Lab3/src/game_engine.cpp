#include "game_engine.h"

using namespace lab3;

GameEngine::GameEngine()
    : is_finished_(false)
{
}

GameEngine::~GameEngine()
{
    // ** Destroy places
    for(Place* p : this->places_)
    {
        delete p;
    }

//    // ** Destroy objects
//    for(std::size_t i = 0; i < this->objects_.size(); ++i)
//    {
//        Object* o = this->objects_[i];
//        delete o;
//    }

    // ** Destroy characters
    for(Character*c : this->characters_)
    {
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
    lab3::utils_io::clearScreen();
    lab3::utils_io::print_newline(this->introduction_);
    lab3::utils_io::wait_for_enter();
    // ** Create places
    home_               = new places::Home("Player's Home");
    Place* old_house    = new places::House("Old House", false);
    Place* hospital     = new places::Hospital("Hospital");
    Place* food_shop    = new places::Multi_Shop("Food Shop", true);
    Place* armory       = new places::Armory("Armory",true);
    Place* forest       = new places::Forest("Enchanted Forest");
    Place* castle       = new places::Castle("Kings Castle", false);
    Place* cave         = new places::Cave("Dark Cave");

    this->places_.push_back(home_);
    this->places_.push_back(old_house);
    this->places_.push_back(hospital);
    this->places_.push_back(forest);
    this->places_.push_back(castle);
    this->places_.push_back(food_shop);
    this->places_.push_back(armory);
    this->places_.push_back(cave);


    // ** Create main characters
    player_ = new characters::Player("Brave Player",home_, home_);
    this->characters_.push_back(player_);
    this->characters_.push_back(new characters::Princess("Trapped Princess",castle));
    this->characters_.push_back(new characters::Wise_Man("Wise Man",old_house));
    this->characters_.push_back(new characters::FinalMonster("Powerful Final Monster", castle));


    // ** Create random animals in forest and cave
    std::vector<places::Outdoor*> animal_places = {static_cast<places::Outdoor*>(forest),
                                                   static_cast<places::Outdoor*>(cave)};
    this->createAnimals(this->characters_, animal_places);

    // ** Create random objects
    std::vector<Place*> object_places = {food_shop, armory, forest, cave};
    this->createObjects(this->objects_, object_places);

    // ** Connect places
    lab3::places::connectPlaces(*home_, *forest, DIRECTION_NORTH);
    lab3::places::connectPlaces(*home_, *food_shop, DIRECTION_EAST);
    lab3::places::connectPlaces(*food_shop, *armory, DIRECTION_WEST);
    lab3::places::connectPlaces(*home_, *food_shop, DIRECTION_EAST);
    lab3::places::connectPlaces(*home_, *old_house, DIRECTION_WEST);
    lab3::places::connectPlaces(*home_, *hospital, DIRECTION_SOUTH);
    lab3::places::connectPlaces(*forest, *castle, DIRECTION_EAST);
    lab3::places::connectPlaces(*forest, *cave, DIRECTION_WEST);
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
        std::vector<Character*> total_characters(characters_);

        std::cout << "Round "<<round++<<std::endl;
        // ** Sort by initiative
        std::sort(total_characters.begin(), total_characters.end(),
                  [](Character* char1, Character* char2)
                  {return 100*char1->isFighting() + char1->getInitiative() >
                          100*char2->isFighting() + char2->getInitiative();});

        // ** Run actions
        for(Character *c : total_characters)
        {
            if(c!= nullptr && c->isAlive())
            {
                // ** Execute action
                std::string event = c->action(c->currentPlace() == player_->currentPlace()); // Switch to true to see all messages

                // ** Process event
                GameEngineFptr fptr = this->event_callbacks_.at(event);
                (this->*fptr)();

                if(is_finished_)
                    break;
                lab3::utils_io::wait_for_enter();
            }
        }
        // ** Put player in hospital if dead
        if(!player_->isAlive())
        {
            lab3::utils_io::print_newline("The player has been seriosly injured. He was translated back home, "
                                          "where it now recovers from the attack...");
            lab3::utils_io::wait_for_enter();
            home_->enter(*player_);
            std::cout << "AFTER ENTERING HOME" << std::endl;
        }

        // ** Remove dead characters
        std::vector<Character*> tmp;
        for(Character* c : characters_)
        {
            if (!c->isAlive())
            {
                // Remove from place
                std::cout << "REMOVING "<<c->name()<<std::endl;
                c->currentPlace()->leave(*c);
                delete c;
                c = nullptr;
                continue;
            }
            tmp.push_back(c);
        }
        characters_ = tmp;

        // ** Create more dynamic objects (restock potions, animals etc)
        regenerateStuff();
    }
    lab3::utils_io::print_newline("Thanks for playing!");
}

void GameEngine::createAnimals(std::vector<Character *> &characters,
                               std::vector<places::Outdoor *> &animalPlaces)
{
    for(places::Outdoor* place : animalPlaces)
    {
        place->generateAnimals();
        for(Character* c: place->characters())
            characters.push_back(c);
    }
}

void GameEngine::createObjects(std::vector<Object*> &objects,
                               std::vector<Place *> &objectPlaces)
{
    for(Place *p : objectPlaces)
    {
        p->generateObjects();
        const std::vector<Object*> &objs = p->objects();

        for(Object *o : objs)
            objects.push_back(o);
    }
}

void GameEngine::regenerateStuff()
{
    // Stock in the Multi_Shop
    for(Place* p : places_)
    {
        places::Shop *p_shop = dynamic_cast<places::Shop*>(p);
        if(p_shop != nullptr)
        {
            p_shop->restock();
        }
    }
    // Animals
}

// ======================= Event callback functions ==========================
void GameEngine::event_EnoughTrain()
{
    lab3::utils_io::print_newline(">>> The "+player_->name()+" is now trained well enough... <<<");
    lab3::utils_io::wait_for_enter();
    places::House* old_house= static_cast<places::House*>(this->places_[1]); // The Old house
    old_house->setOpen(true);
}

void GameEngine::event_TriedMonster()
{
    // ** The wise man tells you new info
    Character* wise_man = this->characters_[2]; // The wise man
    wise_man->set_talk_msgs({"As you have seen, the "+this->monster_name_+" is extremely strong...",
                            "You will need some help in order to defeat him...",
                            "The legend says there exists a Wizard living in a lake, inside the forest."
                             "He will only appears in exceptional cases, and only to the person that requires "
                             "his help."});
    lab3::utils_io::print_newline(">>> The "+player_->name()+" is now prepared to find the Wizard... <<<");
    lab3::utils_io::wait_for_enter();
}
void GameEngine::event_MentionedWizard()
{
    // ** Create the Mana Lake and the Wizard in it
    Place* lake        = new places::Outdoor("Mana Lake");
    Place* forest      = this->places_[3];

    this->places_.push_back(lake);

    // ** Create wizard
    this->characters_.push_back(new characters::Wizard("Misterious Wizard",lake));

    // ** Connect places
    lab3::places::connectPlaces(*forest, *lake, DIRECTION_WEST);
}

void GameEngine::event_GameFinished()
{
    this->is_finished_ = true;
}
void GameEngine::event_QuitGame()
{
    this->is_finished_ = true;
}

void GameEngine::event_Null(){}
