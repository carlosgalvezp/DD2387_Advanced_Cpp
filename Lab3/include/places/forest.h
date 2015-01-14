#ifndef ENCHANTED_FOREST_H
#define ENCHANTED_FOREST_H

#include <places/outdoor.h>

#include <objects/usable.h>

#define N_ANIMALS_FOREST    2
namespace lab3
{
namespace places
{


class Forest : public Outdoor
{
public:
    Forest();
    Forest(const std::string &name);
    ~Forest();

    void generateObjects();
    void createCharacters();

private:
    int n_days_since_last_reproduction_;
};

}
}
#endif // ENCHANTED_FOREST_H
