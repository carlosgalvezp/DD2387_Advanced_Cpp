#ifndef CAVE_H
#define CAVE_H

#include <places/outdoor.h>
#include <characters/vampire.h>
#define N_ANIMALS_CAVE      1
#define CAVE_MAX_POPULATION 2

namespace lab3
{
namespace places
{

class Cave : public Outdoor
{
public:
    Cave(const std::string &name);

    void generateObjects();
    void createCharacters();

    ~Cave();
};

}
}


#endif // CAVE_H
