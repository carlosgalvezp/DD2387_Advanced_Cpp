#ifndef CITYCENTER_H
#define CITYCENTER_H

#include <places/outdoor.h>
#include <characters/warrior.h>

namespace lab3
{
namespace places
{

class CityCenter : public Outdoor
{
public:
    CityCenter();
    CityCenter(const std::string& name);

    void createCharacters();
    ~CityCenter();
};

}
}

#endif // CITYCENTER_H
