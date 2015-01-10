#ifndef KINGS_CASTLE_H
#define KINGS_CASTLE_H

#include <places/indoor.h>

namespace lab3
{
namespace places
{
class Castle : public Indoor
{
public:
    Castle();
    Castle(const std::string &name, bool is_open);
    ~Castle();

    bool enter(Character &character);
};
}
}



#endif // KINGS_CASTLE_H
