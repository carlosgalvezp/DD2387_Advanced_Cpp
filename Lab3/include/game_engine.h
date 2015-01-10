#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

// STL
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <algorithm>
// Own
#include <object.h>
#include <objects/container.h>
#include <objects/health_potion.h>
#include <objects/strength_potion.h>
#include <objects/key.h>

#include <character.h>
#include <characters/player.h>
#include <characters/princess.h>
#include <characters/vampire.h>
#include <characters/wise_man.h>
#include <characters/wizard.h>
#include <characters/wolf.h>
#include <characters/finalmonster.h>

#include <place.h>
#include <places/home.h>
#include <places/house.h>
#include <places/hospital.h>
#include <places/armory.h>
#include <places/forest.h>
#include <places/multi_shop.h>
#include <places/castle.h>
#include <places/cave.h>

#include <events_def.h>

#include <utils/utils.h>

namespace lab3
{
class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void initGame();
    void run();

private:
    std::vector<Object*> objects_;
    std::vector<Character*> characters_;
    std::vector<Place*> places_;

    bool is_finished_;

    Character* player_;
    Place* home_;

    int mainMenu();
    void newGame();

    void createAnimals(std::vector<Character*> &characters,
                             std::vector<places::Outdoor *> &animalPlaces);
    void createObjects(std::vector<Object *> &objects, std::vector<Place*> &objectPlaces);

    void regenerateStuff();

    // ** Event callback functions
    void event_EnoughTrain();
    void event_TriedMonster();
    void event_MentionedWizard();
    void event_GameFinished();
    void event_QuitGame();
    void event_Null();

    typedef void (GameEngine::*GameEngineFptr)(void);
    const std::map<std::string, GameEngineFptr> event_callbacks_ =
    {
        {EVENT_ENOUGH_TRAIN,        &GameEngine::event_EnoughTrain},
        {EVENT_TRIED_MONSTER,       &GameEngine::event_TriedMonster},
        {EVENT_MENTIONED_WIZARD,    &GameEngine::event_MentionedWizard},
        {EVENT_GAME_FINISHED,       &GameEngine::event_GameFinished},
        {EVENT_QUIT_GAME,           &GameEngine::event_QuitGame},
        {EVENT_NULL,                &GameEngine::event_Null}
    };

    const std::string monster_name_ = "Dark Monster";
    const std::string introduction_ =
            "You wake up at home and all you hear is people crying on the streets. "
            "The news are everywhere: the "+monster_name_+" has invaded the King's Castle, killed"
            "the King and trapped the Princess. You, as a soon-to-be Warrior of the King's Guard,"
            "can't just stay home and decide to go for an adventure to kill the "+monster_name_+" and rescue"
            "the poor Princess...";
};

} // namespace lab3

#endif // GAME_ENGINE_H
