#ifndef OUTDOOR_H
#define OUTDOOR_H

#include <place.h>

namespace lab3
{
namespace places
{

class Outdoor : public Place
{
public:
    Outdoor();
    Outdoor(const std::string &name);
    ~Outdoor();
};

}
}


#endif // OUTDOOR_H
