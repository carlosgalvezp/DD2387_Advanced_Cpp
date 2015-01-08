#include <places/castle.h>

using namespace lab3::places;

Castle::Castle()
{}

Castle::Castle(const std::string &name, bool is_open)
    : Indoor(name, is_open)
{}

Castle::~Castle()
{}

