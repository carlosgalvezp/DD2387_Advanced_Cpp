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

    // ** Destroy characters
    for(auto it = this->characters_map_.begin(); it != this->characters_map_.end(); ++it)
    {
        Character *c = it->second;
        delete c;
    }

    // The objects are destroyed by the place or the character that hold them
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
    this->places_map_.insert(std::make_pair(NAME_CITY_CENTER,new places::CityCenter(NAME_CITY_CENTER)));

    // ** Create main characters
    this->characters_map_.insert(std::make_pair(NAME_PLAYER,       new characters::Player(NAME_PLAYER,this->places_map_.at(NAME_HOME))));
    this->characters_map_.insert(std::make_pair(NAME_PRINCESS,     new characters::Princess(NAME_PRINCESS,this->places_map_.at(NAME_CASTLE))));
    this->characters_map_.insert(std::make_pair(NAME_WISE_MAN,     new characters::Wise_Man(NAME_WISE_MAN,this->places_map_.at(NAME_OLD_HOUSE))));
    this->characters_map_.insert(std::make_pair(NAME_FINAL_MONSTER,new characters::FinalMonster(NAME_FINAL_MONSTER, this->places_map_.at(NAME_CASTLE))));

    // ** Create random animals in forest and cave
    std::vector<places::Outdoor*> character_places = {static_cast<places::Outdoor*>(this->places_map_.at(NAME_FOREST)),
                                                      static_cast<places::Outdoor*>(this->places_map_.at(NAME_CAVE)),
                                                      static_cast<places::Outdoor*>(this->places_map_.at(NAME_CITY_CENTER))};
    this->createCharacters(this->characters_map_, character_places);

    // ** Create random objects
    this->createObjects();

    // ** Connect places
    lab3::places::connectPlaces(*this->places_map_.at(NAME_CITY_CENTER),    *this->places_map_.at(NAME_HOME),       DIRECTION_SOUTH);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_CITY_CENTER),    *this->places_map_.at(NAME_OLD_HOUSE),  DIRECTION_SW);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_CITY_CENTER),    *this->places_map_.at(NAME_HOSPITAL),   DIRECTION_SE);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_CITY_CENTER),    *this->places_map_.at(NAME_MULTI_SHOP), DIRECTION_EAST);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_CITY_CENTER),    *this->places_map_.at(NAME_ARMORY),     DIRECTION_NE);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_CITY_CENTER),    *this->places_map_.at(NAME_FOREST),     DIRECTION_NORTH);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_CITY_CENTER),    *this->places_map_.at(NAME_CAVE),       DIRECTION_NW);
    lab3::places::connectPlaces(*this->places_map_.at(NAME_FOREST),         *this->places_map_.at(NAME_CASTLE),     DIRECTION_NORTH);
}

void GameEngine::run()
{
    lab3::utils_io::clearScreen();
    int round(1);
    while(!this->is_finished_)
    {
        Character* player =characters_map_.at(NAME_PLAYER);

        lab3::utils_io::clearScreen();

        std::cout << "Round "<<round++<<std::endl;
        // ** Sort by initiative
        std::vector<Character*> tmp_character;
        for(std::pair<std::string, Character*> p : characters_map_)
        {
            tmp_character.push_back(p.second);
        }
        std::sort(tmp_character.begin(), tmp_character.end(),
                  [](Character* char1, Character* char2)
                  {return 100*char1->isFighting() + char1->getInitiative() >
                          100*char2->isFighting() + char2->getInitiative();});

        // ** Run actions
        for(Character* c: tmp_character)
        {
            if(c!= nullptr && c->isAlive())
            {
                // ** Execute action
                std::string event = c->action(c->currentPlace() == player->currentPlace()); // Switch to true to see all messages

                // ** Process event
                GameEngineFptr fptr = this->event_callbacks_.at(event);
                (this->*fptr)();

                if(is_finished_)
                    break;
                lab3::utils_io::wait_for_enter();
            }
        }
        // ** Put player in hospital if dead
        if(!player->isAlive())
        {
            lab3::utils_io::print_newline("The player has been seriosly injured. He was translated back home, "
                                          "where it now recovers from the attack...");
            lab3::utils_io::wait_for_enter();
            places_map_.at(NAME_HOME)->enter(*player);
        }

        // ** Remove dead characters
        std::map<std::string, Character*> tmp;
        for(auto it = characters_map_.begin(); it != characters_map_.end(); ++it)
        {
            Character *c = it->second;
            if (!c->isAlive())
            {
                // Remove from place
                c->currentPlace()->leave(*c);
                delete c;
                c = nullptr;
                continue;
            }
            tmp.insert(*it);
        }
        characters_map_= tmp;

        // ** Create more dynamic objects (restock potions, animals etc)
//        regenerateStuff();
    }
    lab3::utils_io::print_newline("Thanks for playing!");
}

void GameEngine::createCharacters(std::map<std::string,Character *> &characters,
                               std::vector<places::Outdoor *> &characterPlaces)
{
    for(places::Outdoor* place : characterPlaces)
    {
        place->createCharacters();
        for(Character* c: place->characters())
            characters.insert(std::make_pair(c->name(),c));
    }
}

void GameEngine::createObjects()
{
    for(std::pair<std::string, Place*> pair : this->places_map_)
    {
        Place* p = pair.second;
        p->generateObjects();
    }

    // Special objects
    Object* torch = new lab3::objects::Torch();
    this->places_map_.at(NAME_OLD_HOUSE)->addObject(*torch);
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
    lab3::utils_io::print_newline(">>> The "+characters_map_.at(NAME_PLAYER)->name()+" is now trained well enough... <<<");
    lab3::utils_io::wait_for_enter();
    places::House* old_house= static_cast<places::House*>(this->places_map_.at(NAME_OLD_HOUSE)); // The Old house
    old_house->setOpen(true);
}

void GameEngine::event_TorchOn()
{
    lab3::utils_io::print_newline(">>> You have turned on the torch. You should see new things now... <<<");
    lab3::utils_io::print_newline(">>> The light has waken up a Furious Troll!!<<<");
    // ** Now the key is visible, and the Troll has been waken up
    Place *cave = this->places_map_.at(NAME_CAVE);
    cave->addObject(*(new objects::Key("Key to the King's Castle",places_map_.at(NAME_CASTLE))));
    characters_map_.insert(std::make_pair(NAME_TROLL, new characters::Troll(NAME_TROLL, cave)));
}

void GameEngine::event_TriedMonster()
{
    // ** The wise man tells you new info
    characters::Wise_Man* wise_man = static_cast<characters::Wise_Man*>(characters_map_.at(NAME_WISE_MAN));
    std::stringstream ss, ss2;
    ss <<"As you have seen, the "<< NAME_FINAL_MONSTER<<" is extremely strong...";
    wise_man->set_talk_msgs({ss.str()+
                             "You will need some help in order to defeat him..."+
                             "The legend says there exists a Wizard living in a lake, inside the forest."
                              "He will only appears in exceptional cases, and only to the person that requires "
                              "his help."});
    wise_man->setTellAboutWizard(true);

    ss2 << ">>> You should probably talk to the "<<NAME_WISE_MAN<<". He will give you advice on how to defeat the "<<NAME_FINAL_MONSTER;

    lab3::utils_io::print_newline(ss2.str());
    lab3::utils_io::wait_for_enter();
}
void GameEngine::event_MentionedWizard()
{
    // ** Create wizard
    this->characters_map_.insert(std::make_pair(NAME_WIZARD,new characters::Wizard(NAME_WIZARD,this->places_map_.at(NAME_FOREST), this->places_map_)));

    lab3::utils_io::print_newline(">>> You see a big light in the forest. It seems like something happened there...<<<");
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
