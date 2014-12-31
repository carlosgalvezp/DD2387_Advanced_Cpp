#ifndef OBJECT_H
#define OBJECT_H

namespace lab3
{
class Object
{
public:
    Object();
    virtual ~Object();

    int weight()         const;
    int volume()         const;
    int price()          const;

private:
    int weight_;
    int volume_;
    int price_;
};

}   //namespace lab3

#endif // OBJECT_H
