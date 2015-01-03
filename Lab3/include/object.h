#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <utils/utils_io.h>

namespace lab3
{
class Object
{
public:
    Object();
    Object(const std::string &name, int price, int volume, int weight);
    virtual ~Object();

    int weight()         const;
    int volume()         const;
    int price()          const;

    std::string name()   const;

    bool operator==(const Object& o) const;
private:
    std::string name_;

    int price_;
    int volume_;
    int weight_;
};

}   //namespace lab3

#endif // OBJECT_H
