#ifndef WIZARD_H
#define WIZARD_H

#include <character.h>

namespace lab3
{
namespace characters
{
class Wizard : public Character
{
public:
    Wizard();
    Wizard(const std::string &name, Place* place);

    std::string action(bool display_info);
    ~Wizard();
};
}
}

#endif // WIZARD_H
