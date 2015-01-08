#ifndef HOME_H
#define HOME_H

#include <places/indoor.h>

namespace lab3
{
namespace places
{

class House : public Indoor
{
public:
    House();
    House(const std::string &name, bool is_open);
    ~House();
};
}
}


#endif // HOME_H
