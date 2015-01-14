#ifndef OUTDOOR_H
#define OUTDOOR_H

#include <place.h>
#include <characters/animal.h>

#define DEFAULT_ANIMAL_MAX_POPULATION   3
namespace lab3
{
namespace places
{

class Outdoor : public Place
{
public:
    Outdoor(const std::string &name, int max_animal_population = DEFAULT_ANIMAL_MAX_POPULATION);

    virtual void createCharacters();
    virtual void reproduceCharacters(std::map<std::string, Character *> &new_characters);

    std::size_t getNumberOfAnimals()    const;
    ~Outdoor();
protected:
    std::size_t max_animal_population_;
};

}
}


#endif // OUTDOOR_H
