#ifndef KEY_H
#define KEY_H

#include <objects/usable.h>
#include <place.h>
#include <places/indoor.h>
namespace lab3
{
namespace objects
{

class Key : public Usable
{
public:
    Key();
    Key(const std::string &name, lab3::Place* place);

    bool use(Character &c);

    Place* getPlace()   const;
    ~Key();

private:
    lab3::Place* place_;
};

}
}



#endif // KEY_H
