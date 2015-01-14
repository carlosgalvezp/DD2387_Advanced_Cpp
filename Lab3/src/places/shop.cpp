#include <places/shop.h>

using namespace lab3::places;

Shop::Shop()
{}

Shop::Shop(const std::string &name, bool is_open)
    : Indoor(name, is_open),
      days_since_last_restock_(DAYS_TO_RESTOCK)
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
    if(days_since_last_restock_++ > DAYS_TO_RESTOCK)
    {
        lab3::utils_io::print_newline("============ The shop "+this->name()+" has restocked all of its items ============");
        lab3::utils_io::wait_for_enter();
        days_since_last_restock_ = 0;
    }
}
