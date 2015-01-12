#ifndef WIZARD_H
#define WIZARD_H

#include <characters/human.h>

namespace lab3
{
namespace characters
{
class Wizard : public Human
{
public:
    Wizard(const std::string &name, Place* place,std::map<std::string, Place*>& world_places);

    std::string action(bool display_info);
    void talk_to(Character &character);

    void recover_magic();
    bool teleport(const std::string& place); // the "go" version, but to anywhere
    ~Wizard();

private:
    bool talked_to_player_;
    std::map<std::string, Place*>& world_places_;
    int magic_points_;      //Available points to use his magic
};
}
}

#endif // WIZARD_H
