#include <places/cave.h>

using namespace lab3;
using namespace lab3::places;

Cave::Cave()
{}

Cave::Cave(const std::string &name)
    : Outdoor(name)
{}

Cave::~Cave()
{}

void Cave::generateObjects()
{

}

void Cave::generateAnimals()
{
    new characters::Vampire("Vampire 1", this);
    new characters::Vampire("Vampire 2", this);
}
