#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <sstream>
#include <utils/utils_io.h>

#include <names.h>

namespace lab3
{
class Object
{
public:
    Object(const std::string &name,
           const std::string &description,
           int price,
           int volume,
           int weight);

    virtual ~Object();

    virtual std::string name()          const;
    virtual std::string description()   const;

    int weight()                        const;
    int volume()                        const;
    int price()                         const;

    bool operator==(const Object& o)    const;

private:
    std::string name_;
    std::string description_;

    int price_;
    int volume_;
    int weight_;
};

}   //namespace lab3

#endif // OBJECT_H
