#include <places/citycenter.h>

using namespace lab3::places;

CityCenter::CityCenter(const std::string &name)
    : Outdoor(name)
{}

CityCenter::~CityCenter()
{}

void CityCenter::createCharacters()
{
    new characters::Warrior("warrior 1", this);
//    new characters::Warrior("warrior 2", this);
}

