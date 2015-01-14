#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <object.h>

namespace lab3
{
namespace objects
{

class Equipment : public Object
{
public:
    Equipment(const std::string &name, const std::string &description,
              int price,
              int volume,
              int weight);

    int wear () const;
    void repair();

    ~Equipment();

protected:
    int wear_;
};

}
}


#endif // EQUIPMENT_H
