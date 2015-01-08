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

bool FinalMonster::action()
{
    std::cout << "[FinalMonster::action] TO DO" << std::endl;
    return false;
}

std::string FinalMonster::type() const
{
    return TYPE_FINAL_MONSTER;
}
