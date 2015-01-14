#ifndef WIZARD_H
#define WIZARD_H

#include <characters/human.h>

#define WIZARD_RECOVER_MAGIC_POINTS     20
#define WIZARD_MAX_MAGIC_POINTS         50

namespace lab3
{
namespace characters
{
class Wizard : public Human
{
public:
    Wizard(const std::string &name, Place* place,std::map<std::string, Place*>& world_places);
    ~Wizard();

    ActionResult action(bool display_info);
    ActionResult talk_to(Character &character);

    ActionResult teleport(Place &place); // the "go" version, but to anywhere

    int getMagicPoints()    const;


private:
    bool talked_to_player_;
    int magic_points_;      //Available points to use his magic
    std::map<std::string, Place*>& world_places_;

    void recover_magic();
};
}
}

#endif // WIZARD_H
