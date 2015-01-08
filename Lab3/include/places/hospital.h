#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <places/indoor.h>

namespace lab3
{
namespace places
{
class Hospital : public Indoor
{
public:
    Hospital();
    Hospital(const std::string &name);
    ~Hospital();
};
}
}


#endif // HOSPITAL_H
