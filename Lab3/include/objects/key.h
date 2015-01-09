#ifndef KEY_H
#define KEY_H

#include <objects/item.h>
#include <place.h>
#include <places/indoor.h>
namespace lab3
{
namespace objects
{

class Key : public Item
{
public:
    Key();
    Key(const std::string &name, lab3::Place* place);

    bool use(Character &c);
    ~Key();

private:
    lab3::Place* place_;
};

}
}



#endif // KEY_H
