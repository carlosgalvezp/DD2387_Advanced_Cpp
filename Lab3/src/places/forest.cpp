#include <places/forest.h>
#include <characters/wolf.h>

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
    Object *o = new objects::Item("torch", "It illuminates the place if you turn it on", 5, 5, 5);
    this->objects_.push_back(o);
}

void Forest::generateAnimals()
{
    new characters::Wolf("Wolf 1", this);
    new characters::Wolf("Wolf 2", this);
    new characters::Wolf("Wolf 3", this);
}
