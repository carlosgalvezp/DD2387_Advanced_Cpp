#ifndef WISE_MAN_H
#define WISE_MAN_H

#include <characters/human.h>

namespace lab3
{
namespace characters
{
class Wise_Man : Human
{
public:
    Wise_Man();
    Wise_Man(const std::string &name);

    ~Wise_Man();
};
}
}

#endif // WISE_MAN_H
