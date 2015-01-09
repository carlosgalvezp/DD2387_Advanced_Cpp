#include <characters/vampire.h>

using namespace lab3::characters;

Vampire::Vampire()
{}

Vampire::Vampire(const std::string &name, Place* place)
    : Animal (name, TYPE_VAMPIRE, place)
{}

Vampire::~Vampire()
{}

