#ifndef PRINCESS_H
#define PRINCESS_H

#include <character.h>

namespace lab3
{
namespace characters
{
class Princess : public Character
{
public:
    Princess();
    ~Princess();

    std::string type() const;
};

}
}

#endif // PRINCESS_H
