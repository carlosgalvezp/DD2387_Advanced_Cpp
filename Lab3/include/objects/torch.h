#ifndef TORCH_H
#define TORCH_H

#include <objects/usable.h>

namespace lab3
{
namespace objects
{

class Torch : public Usable
{
public:
    Torch();
    ~Torch();

    ActionResult use(Character &c);
};

}

}

#endif // TORCH_H
