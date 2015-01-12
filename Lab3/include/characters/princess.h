#ifndef PRINCESS_H
#define PRINCESS_H

#include <characters/human.h>
#include <utils/utils_io.h>
#include <characters/finalmonster.h>

namespace lab3
{
namespace characters
{
class Princess : public Human
{
public:
    Princess();
    Princess(const std::string& name, Place *place);
    ~Princess();

    std::string action(bool display_info);
    std::string type() const;

    bool distractMonster(characters::FinalMonster& monster);

private:
    int hope_;  // Hope that she gets rescued.
                // If it's high, she will get more ideas to distract the monster
};

}
}

#endif // PRINCESS_H
