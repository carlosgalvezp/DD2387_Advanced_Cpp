#include <characters/finalmonster.h>

using namespace lab3;
using namespace lab3::characters;

FinalMonster::FinalMonster()
{}

FinalMonster::FinalMonster(const std::string &name, Place *place)
    : Character(name, TYPE_FINAL_MONSTER, place)
{}

FinalMonster::~FinalMonster()
{}

std::string FinalMonster::action(bool display_info)
{
    std::cout << "[FinalMonster::action] TO DO" << std::endl;
    return EVENT_NULL;
}

std::string FinalMonster::type() const
{
    return TYPE_FINAL_MONSTER;
}
