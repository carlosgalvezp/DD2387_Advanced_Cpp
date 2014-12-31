#ifndef CONTAINER_H
#define CONTAINER_H

// STL
#include <vector>

#include "object.h"

namespace lab3
{
namespace object
{
/**
 * @brief The Container class
 * Represents a container: it is an object that itself can contain more objects
 */
class Container : Object
{
public:
    Container();

    double hold_weight()    const;
    double hold_volume()    const;

    bool add(const Object& object);
    bool remove(const Object& object);

private:
    std::vector<Object *> objects_;
};

}   //namespace object
}   //namespace lab3


#endif // CONTAINER_H
