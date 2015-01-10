#ifndef WISE_MAN_H
#define WISE_MAN_H

#include <characters/human.h>

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

    std::string action();
    void talk_to(Character &c);

    void setTellAboutWizard(bool x);
private:
    bool will_tell_about_wizard_;
};
}
}

#endif // WISE_MAN_H
