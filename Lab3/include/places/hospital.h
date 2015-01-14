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
    explicit Hospital(const std::string &name);
    ~Hospital();

    bool cure(characters::Human &c) const;

};
}
}


#endif // HOSPITAL_H
