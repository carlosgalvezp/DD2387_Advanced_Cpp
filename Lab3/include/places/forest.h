#ifndef ENCHANTED_FOREST_H
#define ENCHANTED_FOREST_H

#include <places/outdoor.h>

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
};

}
}
#endif // ENCHANTED_FOREST_H
