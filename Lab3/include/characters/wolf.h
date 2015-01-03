#ifndef WOLF_H
#define WOLF_H

#include <characters/animal.h>

namespace lab3
{
namespace characters
{
class Wolf : Animal
{
public:
    Wolf();
    Wolf(const std::string &name);
    ~Wolf();
};
}
}
#endif // WOLF_H
