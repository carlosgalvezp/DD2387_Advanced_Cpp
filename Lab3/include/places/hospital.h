#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <places/indoor.h>
#include <characters/human.h>

#define CURE_PRICE 10
namespace lab3
{
namespace places
{
class Hospital : public Indoor
{
public:
    Hospital();
    Hospital(const std::string &name);

    bool cure(characters::Human &c) const;

    ~Hospital();
};
}
}


#endif // HOSPITAL_H
