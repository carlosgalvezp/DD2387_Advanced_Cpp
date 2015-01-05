#include <characters/wolf.h>

namespace lab3
{
namespace characters
{

Wolf::Wolf()
{}

Wolf::Wolf(const std::string &name, Place *place)
    : Animal(name, TYPE_WOLF, place)
{}

Wolf::~Wolf()
{}


std::string Wolf::type() const
{
    return "Wolf";
}

}
}


