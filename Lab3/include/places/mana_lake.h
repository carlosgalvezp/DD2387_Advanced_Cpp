#ifndef MANA_LAKE_H
#define MANA_LAKE_H

#include <places/outdoor.h>

namespace lab3
{
namespace places
{

class Mana_Lake : public Outdoor
{
public:
    Mana_Lake();
    Mana_Lake(const std::string &name);
    ~Mana_Lake();
};

}
}



#endif // MANA_LAKE_H
