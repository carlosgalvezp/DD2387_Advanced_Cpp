#ifndef OBJECT_H
#define OBJECT_H

namespace lab3
{
class Object
{
public:
    Object();

    double weight()         const;
    double volume()         const;
    double price()          const;
};

}   //namespace lab3

#endif // OBJECT_H
