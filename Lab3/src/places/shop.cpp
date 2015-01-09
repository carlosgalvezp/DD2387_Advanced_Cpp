#include <places/shop.h>

using namespace lab3::places;

Shop::Shop()
{}

Shop::Shop(const std::string &name, bool is_open)
    : Indoor(name, is_open),
      days_to_restock_(DAYS_TO_RESTOCK)
{}


Shop::~Shop()
{}

void Shop::restock()
{
    --days_to_restock_;
    if(days_to_restock_ == 0)
    {
        lab3::utils_io::print_newline("The shop "+this->name()+" has restocked all of its items");
        days_to_restock_ = 0;
    }
}
