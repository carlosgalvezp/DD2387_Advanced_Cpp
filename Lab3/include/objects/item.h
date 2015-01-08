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
         int volume);

    virtual void use(Character &c);
    ~Item();
};

}
}

#endif // ITEM_H
