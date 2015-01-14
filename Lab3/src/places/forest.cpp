#include <places/forest.h>
#include <characters/wolf.h>
#include <objects/torch.h>


using namespace lab3::places;

Forest::Forest(const std::string &name)
    : Outdoor(name)
{}


Forest::~Forest()
{}

void Forest::generateObjects()
{
}

void Forest::createCharacters()
{
    for(int i = 0; i < N_ANIMALS_FOREST; ++i)
    {
        new characters::Wolf(this, this);
    }
}
