#include <places/shop.h>

using namespace lab3::places;

Shop::Shop()
{}

Shop::Shop(const std::string &name, bool is_open)
    : Indoor(name, is_open)
{}

Shop::~Shop()
{}

