#include <places/forest.h>
#include <characters/wolf.h>
#include <objects/torch.h>

#define FOREST_MAX_POPULATION 5

using namespace lab3::places;

Forest::Forest()
{}

Forest::Forest(const std::string &name)
    : Outdoor(name)
{}


Forest::~Forest()
{}

void Forest::generateObjects()
{
    std::cout << "[Forest::generateObjects] TO DO" << std::endl;
}

void Forest::createCharacters()
{
    for(int i = 0; i < N_ANIMALS_FOREST; ++i)
    {
        new characters::Wolf(this, this);
    }
}
