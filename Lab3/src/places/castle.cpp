#include <places/castle.h>


using namespace lab3::places;
using namespace lab3;

Castle::Castle()
{}

Castle::Castle(const std::string &name, bool is_open)
    : Indoor(name, is_open)
{}

Castle::~Castle()
{}

bool Castle::enter(Character &character)
{
    return Indoor::enter(character);
}

