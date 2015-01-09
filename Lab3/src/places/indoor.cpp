#include <places/indoor.h>

using namespace lab3::places;

Indoor::Indoor()
{}

Indoor::Indoor(const std::string &name, bool is_open)
    : Place(name), is_open_(is_open)
{}


Indoor::~Indoor()
{}

void Indoor::open(){ this->is_open_ = true;}


