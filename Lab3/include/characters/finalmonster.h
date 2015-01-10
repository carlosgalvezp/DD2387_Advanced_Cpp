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

    bool fight(Character &character);

    std::string action(bool display_info);
    std::string type() const;

private:
    bool defeated_player_;
};

}
}

#endif // FINALMONSTER_H
