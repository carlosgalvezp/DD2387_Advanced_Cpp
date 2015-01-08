#ifndef PROTECTION_H
#define PROTECTION_H

#include <object.h>

namespace lab3
{
namespace objects
{
class Protection : Object
{
public:
    Protection();
    ~Protection();

    int defensePoints() const;

protected:
    int defense_;
};

}
}

#endif // PROTECTION_H
