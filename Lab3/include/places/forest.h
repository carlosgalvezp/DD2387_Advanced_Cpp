#ifndef ENCHANTED_FOREST_H
#define ENCHANTED_FOREST_H

#include <places/outdoor.h>

#include <objects/item.h>

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
    void generateAnimals();

    ~Forest();
};

}
}
#endif // ENCHANTED_FOREST_H
