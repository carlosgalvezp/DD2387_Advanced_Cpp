#ifndef CONTAINER_H
#define CONTAINER_H

// STL
#include <vector>

#include "object.h"
#include <sstream>
namespace lab3
{
namespace objects
{
/**
 * @brief The Container class
 * Represents a container: it is an object that itself can contain more objects
 */
class Container : public Object
{
public:
    Container(const std::string &name, int price, int volume, int weight, int max_volume,int max_weight);
    ~Container();

    int max_hold_weight()         const;
    int max_hold_volume()         const;
    int current_hold_volume()     const;
    int current_hold_weight()     const;

    bool add(Object &object);
    bool remove(const Object& object);

    const std::vector<Object*> & objects()  const;

    std::string description()               const;

    bool operator > (const Container& c)    const;

    bool isMovableTo(const Container &c)    const;

    bool moveObjectsTo(Container &c);


private:
    std::vector<Object *> objects_;
    int max_hold_weight_;
    int max_hold_volume_;
    int current_hold_weight_;
    int current_hold_volume_;
};

}   //namespace object
}   //namespace lab3


#endif // CONTAINER_H
