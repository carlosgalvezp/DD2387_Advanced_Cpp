#include <places/outdoor.h>

using namespace lab3::places;

Outdoor::Outdoor()
{}

Outdoor::Outdoor(const std::string &name, int max_animal_population)
    : Place(name), max_animal_population_(max_animal_population)
{}

Outdoor::~Outdoor()
{
}

void Outdoor::createCharacters(){}

std::size_t Outdoor::getNumberOfAnimals()   const
{
    std::size_t result;
    for(Character *c : this->characters())
    {
        if(dynamic_cast<characters::Animal*>(c) != nullptr)
            ++result;
    }
    return result;
}


void Outdoor::reproduceCharacters(std::map<std::string, Character *> new_characters)
{
    if(this->getNumberOfAnimals() < max_animal_population_)
    {
        for(Character *c : this->characters())
        {
            characters::Animal* c_animal = dynamic_cast<characters::Animal*>(c);
            if(c_animal != nullptr)
            {
                Character *new_c = c_animal->reproduce();
                if(new_c!= nullptr)
                {
                    new_characters.insert(std::make_pair(new_c->name(), new_c));
                }
            }
        }
    }
}
