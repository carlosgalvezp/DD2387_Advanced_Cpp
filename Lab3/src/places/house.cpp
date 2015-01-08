#include <places/house.h>

using namespace lab3::places;

House::House()
{}

House::House(const std::string &name, bool is_open)
    : Indoor(name, is_open)
{}

House::~House()
{}

