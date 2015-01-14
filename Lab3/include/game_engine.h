#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

// STL
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>

// Own
#include <object.h>
#include <objects/container.h>
#include <objects/health_potion.h>
#include <objects/strength_potion.h>
#include <objects/key.h>
#include <objects/torch.h>

#include <character.h>
#include <characters/player.h>
#include <characters/princess.h>
#include <characters/vampire.h>
#include <characters/wise_man.h>
#include <characters/wizard.h>
#include <characters/wolf.h>
#include <characters/troll.h>
#include <characters/finalmonster.h>
#include <characters/warrior.h>

#include <place.h>
#include <places/home.h>
#include <places/house.h>
#include <places/hospital.h>
#include <places/armory.h>
#include <places/forest.h>
#include <places/multi_shop.h>
#include <places/castle.h>
#include <places/cave.h>
#include <places/citycenter.h>

#include <names.h>

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
    std::map<std::string, Character*> characters_map_;
    std::map<std::string, Place*> places_map_;

    bool is_finished_;
    std::string introduction_;
    std::string ending_;


    int mainMenu();
    void newGame();

    void createCharacters(std::map<std::string, Character *> &characters,
                             std::vector<places::Outdoor *> &animalPlaces);
    void createObjects();

    void regenerateStuff(std::map<std::string, Character *> &characters);

    // ** Event callback functions
    void event_EnoughTrain();
    void event_TorchOn();
    void event_TriedMonster();
    void event_MentionedWizard();
    void event_GameFinished();
    void event_QuitGame();
    void event_Null();

    typedef void (GameEngine::*GameEngineFptr)(void);
    const std::map<std::string, GameEngineFptr> event_callbacks_ =
    {
        {EVENT_ENOUGH_TRAIN,        &GameEngine::event_EnoughTrain},
        {EVENT_TORCH_ON,            &GameEngine::event_TorchOn},
        {EVENT_TRIED_MONSTER,       &GameEngine::event_TriedMonster},
        {EVENT_MENTIONED_WIZARD,    &GameEngine::event_MentionedWizard},
        {EVENT_GAME_FINISHED,       &GameEngine::event_GameFinished},
        {EVENT_QUIT_GAME,           &GameEngine::event_QuitGame},
        {EVENT_NULL,                &GameEngine::event_Null}
    };


};

} // namespace lab3

#endif // GAME_ENGINE_H
