#include <objects/torch.h>

using namespace lab3::objects;

Torch::Torch()
    : Item("torch", "It illuminates the place if you use it", 10,5,5, true)
{}

Torch::~Torch()
{}

bool Torch::use(Character &c)
{
    if(c.currentPlace()->name() == NAME_CAVE)
    {
        throw std::runtime_error(EVENT_TORCH_ON);
    }
    else
    {
        lab3::utils_io::print_newline("You cannot use the torch here, it's already light enough.");
        return false;
    }
}
