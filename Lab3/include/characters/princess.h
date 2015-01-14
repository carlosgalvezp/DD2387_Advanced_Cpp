#ifndef PRINCESS_H
#define PRINCESS_H

#include <characters/human.h>
#include <utils/utils_io.h>
#include <characters/finalmonster.h>

#define HOPE_MAX        10

namespace lab3
{
namespace characters
{
class Princess : public Human
{
public:
    Princess(const std::string& name, Place *place);
    ~Princess();

    ActionResult action(bool display_info);

    void addHope(int hope);
    int getHope()                   const;

private:
    int hope_;  // Hope that she gets rescued.
                // If it's high, she will get more ideas to distract the monster

    ActionResult distractMonster(characters::FinalMonster& monster) const;
};

}
}

#endif // PRINCESS_H
