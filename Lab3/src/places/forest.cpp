#include <places/forest.h>
#include <characters/wolf.h>
#include <objects/torch.h>

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
    new characters::Wolf("wolf 1", this, this);
    new characters::Wolf("wolf 2", this, this);
}
