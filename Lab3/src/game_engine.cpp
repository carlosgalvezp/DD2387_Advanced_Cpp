#include "game_engine.h"

using namespace lab3;

GameEngine::GameEngine()
    : is_finished_(false)
{
    std::stringstream ss1, ss2;

    ss1 << "You wake up at home and all you hear is people crying on the streets. "
          "The news are everywhere: the "<<NAME_FINAL_MONSTER<<" has invaded the "<<NAME_CASTLE<<", killed "
    "the King and trapped the "<<NAME_PRINCESS<<". You, as a soon-to-be Warrior of the King's Guard, "
    "can't just stay home and decide to go for an adventure to kill the "<<NAME_FINAL_MONSTER<<" and rescue "
    "the poor Princess...";

    introduction_ = ss1.str();

    ss2 << "The " <<  NAME_FINAL_MONSTER << " has been defeated thanks to the joint effort of the "
        << NAME_PLAYER<< " and the " << NAME_WIZARD << "! The "<< NAME_PRINCESS <<" has been rescued and you have been "
               <<" achieved the King's Guard Leader position, ready for new adventures to come...";

    ending_ = ss2.str();
}

GameEngine::~GameEngine()
{
    // ** Destroy places
    for(auto it = this->places_map_.begin(); it != this->places_map_.end(); ++it)
    {
        Place*p = it->second;
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
    this->places_map_.insert(std::make_pair(NAME_HOME,      new places::Home(NAME_HOME)));
    this->places_map_.insert(std::make_pair(NAME_OLD_HOUSE, new places::House(NAME_OLD_HOUSE, false)));
    this->places_map_.insert(std::make_pair(NAME_HOSPITAL,  new places::Hospital(NAME_HOSPITAL)));
    this->places_map_.insert(std::make_pair(NAME_MULTI_SHOP,new places::Multi_Shop(NAME_MULTI_SHOP, true)));
    this->places_map_.insert(std::make_pair(NAME_ARMORY,    new places::Armory(NAME_ARMORY, true)));
    this->places_map_.insert(std::make_pair(NAME_FOREST,    new places::Forest(NAME_FOREST)));
    this->places_map_.insert(std::make_pair(NAME_CASTLE,    new places::Castle(NAME_CASTLE, false)));
    this->places_map_.insert(std::make_pair(NAME_CAVE,      new places::Cave(NAME_CAVE)));

    // ** Create main characters
    player_ = new characters::Player(NAME_PLAYER,this->places_map_.at(NAME_HOME));
    this->characters_.push_back(player_);
    this->characters_.push_back(new characters::Princess("Trapped Princess",this->places_map_.at(NAME_CASTLE)));
    this->characters_.push_back(new characters::Wise_Man("Wise Man",this->places_map_.at(NAME_OLD_HOUSE)));
    this->characters_.push_back(new characters::FinalMonster("Powerful Final Monster", this->places_map_.at(NAME_CASTLE)));


    // ** Create random animals in forest and cave
    std::vector<places::Outdoor*> animal_places = {static_cast<places::Outdoor*>(this->places_map_.at(NAME_FOREST)),
                                                   static_cast<places::Outdoor*>(this->places_map_.at(NAME_CAVE))};
    this->createAnimals(this->characters_, animal_places);

    // ** Create random objects
    std::vector<Place*> object_places = {this->places_map_.at(NAME_MULTI_SHOP),
                                         this->places_map_.at(NAME_ARMORY),
                                         this->places_map_.at(NAME_FOREST),
                                         this->places_map_.at(NAME_CAVE)};
    this->createObjects(this->objects_, object_places);

    // ** Connect places
    lab3::places::connectPlaces(*this->places_map_.at(NAME_HOME), *this->places_map_.at(NAME_FOREST), DIRECTION_NORTH);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_HOME), *this->places_map_.at(NAME_MULTI_SHOP), DIRECTION_EAST);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_MULTI_SHOP), *this->places_map_.at(NAME_ARMORY), DIRECTION_WEST);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_HOME), *this->places_map_.at(NAME_OLD_HOUSE), DIRECTION_WEST);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_HOME), *this->places_map_.at(NAME_HOSPITAL), DIRECTION_SOUTH);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_FOREST), *this->places_map_.at(NAME_CASTLE), DIRECTION_EAST);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_FOREST), *this->places_map_.at(NAME_CAVE), DIRECTION_WEST);

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

        // ** Create more dynamic objects (restock potions, animals etc)
//        regenerateStuff();
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
    for(auto it = this->places_map_.begin(); it != this->places_map_.end(); ++it)
    {
        Place* p = it->second;
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
    places::House* old_house= static_cast<places::House*>(this->places_map_.at(NAME_OLD_HOUSE)); // The Old house
    old_house->setOpen(true);
}

void GameEngine::event_TorchOn()
{
    lab3::utils_io::print_newline(">>> You have turned on the torch. You should see new things now... <<<");
    Place *cave = this->places_map_.at(NAME_CAVE);
    cave->addObject(*(new objects::Item("key","The key to open the King's Castle",1000,0,0, false)));
}

void GameEngine::event_TriedMonster()
{
    // ** The wise man tells you new info
    Character* wise_man = this->characters_[2]; // The wise man
    std::stringstream ss;
    ss <<"As you have seen, the "<< NAME_FINAL_MONSTER<<" is extremely strong...";
    wise_man->set_talk_msgs({ss.str(),
                             "You will need some help in order to defeat him...",
                             "The legend says there exists a Wizard living in a lake, inside the forest."
                              "He will only appears in exceptional cases, and only to the person that requires "
                              "his help."});
    lab3::utils_io::print_newline(">>> The "+player_->name()+" is now prepared to find the Wizard... <<<");
    lab3::utils_io::wait_for_enter();
}
void GameEngine::event_MentionedWizard()
{
    // ** Create wizard
    this->characters_.push_back(new characters::Wizard(NAME_WIZARD,this->places_map_.at(NAME_FOREST)));

    lab3::utils_io::print_newline(">>>You see a big light in the forest. It seems like something happened there...<<<");
}

void GameEngine::event_GameFinished()
{
    this->is_finished_ = true;
    lab3::utils_io::print_newline(this->ending_);
    lab3::utils_io::wait_for_enter();
}
void GameEngine::event_QuitGame()
{
    this->is_finished_ = true;
}

void GameEngine::event_Null(){}
