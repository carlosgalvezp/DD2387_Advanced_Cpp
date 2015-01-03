#ifndef ENCHANTED_FOREST_H
#define ENCHANTED_FOREST_H

#include <place.h>

namespace lab3
{
namespace places
{


class Enchanted_Forest : public Place
{
public:
    Enchanted_Forest();
    Enchanted_Forest(const std::string &name);
    ~Enchanted_Forest();
};

}
}
#endif // ENCHANTED_FOREST_H
