#ifndef INDOOR_H
#define INDOOR_H

#include <place.h>
#include <objects/container.h>
#include <objects/key.h>
namespace lab3
{
namespace objects
{
class Key;
}

namespace places
{

class Indoor : public Place
{
public:
    Indoor();
    Indoor(const std::string &name, bool is_open);
    ~Indoor();

    bool isOpen()               const;
    void setOpen(bool open);

    bool enter(Character &character);

protected:
    bool is_open_;

    bool isValidKey(const lab3::objects::Key& key)       const;
};

}
}

#endif // INDOOR_H
