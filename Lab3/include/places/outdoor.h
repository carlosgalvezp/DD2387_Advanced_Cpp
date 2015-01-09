#ifndef OUTDOOR_H
#define OUTDOOR_H

#include <place.h>
#include <characters/animal.h>

namespace lab3
{
namespace places
{

class Outdoor : public Place
{
public:
    Outdoor();
    Outdoor(const std::string &name);

    virtual void generateAnimals();
    ~Outdoor();
protected:
    std::vector<characters::Animal> animals_;
};

}
}


#endif // OUTDOOR_H
