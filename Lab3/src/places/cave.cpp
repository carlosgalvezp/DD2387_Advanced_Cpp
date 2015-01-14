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

void Cave::createCharacters()
{
    for(int i = 0; i < N_ANIMALS_CAVE; ++i)
    {
        new characters::Vampire(this, this);
    }
}
