#ifndef FINALMONSTER_H
#define FINALMONSTER_H

#include <character.h>
#include <types.h>
namespace lab3
{
namespace characters
{

class FinalMonster : public Character
{
public:
    FinalMonster();
    FinalMonster(const std::string &name, Place* place);
    ~FinalMonster();

    std::string action();
    std::string type() const;
};

}
}

#endif // FINALMONSTER_H
