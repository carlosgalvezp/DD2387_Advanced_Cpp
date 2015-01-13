#ifndef TROLL_H
#define TROLL_H

#include <characters/animal.h>

namespace lab3
{
namespace characters
{

class Troll : public Animal
{
public:
    Troll();
    Troll(const std::string &name, Place *place);

    std::string action(bool display_info); // == 0

    ~Troll();

private:
    int stupidity_;  // As we all know, Trolls are not so smart. The larger this value,
                     // the more non-sensible actions they perform
    bool isEnemy(const Character &ch) const;
};

}
}

#endif // TROLL_H
