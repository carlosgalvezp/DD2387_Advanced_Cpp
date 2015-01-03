#ifndef OBJECT_H
#define OBJECT_H

#include <string>

namespace lab3
{
class Object
{
public:
    Object();
    Object(const std::string &name);
    virtual ~Object();

    int weight()         const;
    int volume()         const;
    int price()          const;

    std::string name()   const;

private:
    int weight_;
    int volume_;
    int price_;

    std::string name_;
};

}   //namespace lab3

#endif // OBJECT_H
