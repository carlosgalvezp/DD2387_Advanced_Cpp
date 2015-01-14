#ifndef USABLE_H
#define USABLE_H

#include <object.h>
#include <character.h>

namespace lab3
{
namespace objects
{

class Usable : public Object
{
public:
    Usable(const std::string &name,
           const std::string &description,
           int price,
           int weight,
           int volume,
           bool is_single_use);
    ~Usable();

    virtual ActionResult use(Character &c);

    bool isSingleUse()   const;

protected:
    bool is_single_use_;
};

}
}

#endif // ITEM_H
