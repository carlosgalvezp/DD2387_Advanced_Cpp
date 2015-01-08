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

    bool action();
};
}
}

#endif // WISE_MAN_H
