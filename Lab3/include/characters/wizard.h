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
    Wizard(const std::string &name, Place* place,std::map<std::string, Place*>& world_places);

    std::string action(bool display_info);
    void talk_to(Character &character);

    bool teleport(const std::string& place);
    ~Wizard();

private:
    bool talked_to_player_;
    std::map<std::string, Place*>& world_places_;
};
}
}

#endif // WIZARD_H
