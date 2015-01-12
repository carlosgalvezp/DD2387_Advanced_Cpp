#ifndef ENCHANTED_FOREST_H
#define ENCHANTED_FOREST_H

#include <places/outdoor.h>

#include <objects/usable.h>

namespace lab3
{
namespace places
{


class Forest : public Outdoor
{
public:
    Forest();
    Forest(const std::string &name);

    void generateObjects();
    void createCharacters();

    ~Forest();
};

}
}
#endif // ENCHANTED_FOREST_H
