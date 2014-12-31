#include "place.h"

using namespace lab3;

Place::Place()
{
}

Place::~Place()
{
    for(Direction* d : directions_)
    {
        delete d;
    }
}

bool Place::enter(Character &character)
{
    this->characters_.push_back(&character);
    return true;
}

bool Place::leave(Character &character)
{
    // ** Find character
    auto it = std::find(this->characters_.begin(), this->characters_.end(), &character);
    if(it != this->characters_.end())
    {
        return false;
    }
    else
    {
        // ** If found, delete it
        this->characters_.erase(it);
        return true;
    }
}

void Place::drop(Object &object)
{
    this->objects_.push_back(&object);
}

bool Place::pick_up(Object &object)
{
    // ** Find character
    auto it = std::find(this->objects_.begin(), this->objects_.end(), &object);
    if(it != this->objects_.end())
    {
        return false;
    }
    else
    {
        // ** If found, delete it
        this->objects_.erase(it);
        return true;
    }
}

void Place::addDirection(Direction *direction)
{
    this->directions_.push_back(direction);
}
