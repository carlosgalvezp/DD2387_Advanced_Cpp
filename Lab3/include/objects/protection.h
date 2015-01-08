#ifndef PROTECTION_H
#define PROTECTION_H

#include <object.h>

namespace lab3
{
namespace objects
{
class Protection : public Object
{
public:
    Protection();
    Protection(const std::string &name,
           int defense_points,
           int price,
           int volume,
           int weight);
    ~Protection();

    int defensePoints() const;

protected:
    int defense_;
};

}
}

#endif // PROTECTION_H
