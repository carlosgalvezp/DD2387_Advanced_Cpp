#include <places/outdoor.h>

using namespace lab3::places;

Outdoor::Outdoor()
{}

Outdoor::Outdoor(const std::string &name)
    : Place(name)
{}

Outdoor::~Outdoor()
{
}

void Outdoor::generateAnimals()
{
    std::cout << "[Outdoor::generateAnimals]"<<std::endl;
}
