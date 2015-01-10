#ifndef ITEM_H
#define ITEM_H

#include <object.h>
#include <character.h>

namespace lab3
{
namespace objects
{

class Item : public Object
{
public:
    Item();
    Item(const std::string &name,
         const std::string &description,
         int price,
         int weight,
         int volume,
         bool is_single_use);
    ~Item();

    virtual bool use(Character &c);

    bool isSingleUse()   const;

protected:
    bool is_single_use_;
};

}
}

#endif // ITEM_H
