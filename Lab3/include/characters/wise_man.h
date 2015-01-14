#ifndef WISE_MAN_H
#define WISE_MAN_H

#include <characters/human.h>

#define WISE_MAN_READ_POINTS    5 // The knowledge is incremented by this amount after reading

namespace lab3
{
namespace characters
{
class Wise_Man : public Human
{
public:
    Wise_Man();
    Wise_Man(const std::string &name, Place *place);
    ~Wise_Man();

    ActionResult action(bool display_info);
    ActionResult talk_to(Character &c);

    void setTellAboutWizard(bool x);

    int getKnowledgePoints()    const;

private:
    bool will_tell_about_wizard_;
    int knowledge_;     // The more it knows, the more hints can give the player

    ActionResult read();                    // It increases its knowledge
};
}
}

#endif // WISE_MAN_H
