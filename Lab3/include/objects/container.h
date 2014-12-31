#ifndef CONTAINER_H
#define CONTAINER_H

// STL
#include <vector>

#include "object.h"

namespace lab3
{
namespace objects
{
/**
 * @brief The Container class
 * Represents a container: it is an object that itself can contain more objects
 */
class Container : Object
{
public:
    Container();

    int hold_weight()    const;
    int hold_volume()    const;

    bool add(const Object& object);
    bool remove(const Object& object);

private:
    std::vector<Object *> objects_;
    int hold_weight_;
    int hold_volume_;
};

}   //namespace object
}   //namespace lab3


#endif // CONTAINER_H
