#ifndef KINGS_CASTLE_H
#define KINGS_CASTLE_H

#include <place.h>

namespace lab3
{
namespace places
{
class Kings_Castle : public Place
{
public:
    Kings_Castle();
    Kings_Castle(const std::string &name);
    ~Kings_Castle();
};
}
}



#endif // KINGS_CASTLE_H