#include <places/shop.h>

using namespace lab3::places;

Shop::Shop()
{}

Shop::Shop(const std::string &name, bool is_open)
    : Indoor(name, is_open),
      days_to_restock_(DAYS_TO_RESTOCK)
{
    std::vector<std::string> tmp;
    for(auto it = this->place_commands_.begin(); it != this->place_commands_.end();++it)
    {
        if(*it != CMD_PICK_UP && *it != CMD_DROP)   // You can't just grab stuff in a shop; rather you buy and sell
            tmp.push_back(*it);
    }
    tmp.push_back(CMD_BUY);
//    tmp.push_back(CMD_SELL);
    this->place_commands_ = tmp;
}


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
