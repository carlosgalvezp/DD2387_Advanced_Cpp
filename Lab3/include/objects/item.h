#ifndef ITEM_H
#define ITEM_H

#include <object.h>

namespace lab3
{
namespace objects
{

class Item : public Object
{
public:
    Item();
    Item(const std::string &name, int price, int weight, int volume);
    ~Item();
};

}
}

#endif // ITEM_H
