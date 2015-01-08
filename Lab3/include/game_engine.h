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
#include <objects/armor.h>
#include <objects/axe.h>
#include <objects/container.h>
#include <objects/health_potion.h>
#include <objects/strength_potion.h>
#include <objects/key.h>
#include <objects/shield.h>
#include <objects/sword.h>

#include <character.h>
#include <characters/player.h>
#include <characters/princess.h>
#include <characters/troll.h>
#include <characters/wise_man.h>
#include <characters/wizard.h>
#include <characters/wolf.h>
#include <characters/finalmonster.h>

#include <place.h>
#include <places/house.h>
#include <places/hospital.h>
#include <places/armory.h>
#include <places/forest.h>
#include <places/multi_shop.h>
#include <places/castle.h>
#include <places/cave.h>

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

    int mainMenu();
    void newGame();

    void createAnimals(std::vector<Character*> &characters,
                             std::vector<Place*> &animalPlaces);
    void createObjects(std::vector<Object *> &objects, std::vector<Place*> &objectPlaces);
};

} // namespace lab3

#endif // GAME_ENGINE_H
