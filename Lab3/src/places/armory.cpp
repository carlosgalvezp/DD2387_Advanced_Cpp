#include <places/armory.h>

using namespace lab3::places;

Armory::Armory()
{}

Armory::Armory(const std::string &name, bool is_open)
    : Shop(name, is_open)
{}

Armory::~Armory()
{}

