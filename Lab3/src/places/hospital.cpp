#include <places/hospital.h>

using namespace lab3::places;

Hospital::Hospital()
{}

Hospital::Hospital(const std::string &name)
    : Indoor(name, true)
{}

Hospital::~Hospital()
{}

