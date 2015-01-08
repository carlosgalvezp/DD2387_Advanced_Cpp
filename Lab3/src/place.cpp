#include "place.h"

using namespace lab3;

Place::Place()
{
}

Place::Place(const std::string &name)
    : name_(name)
{}

Place::~Place()
{
}

void Place::generateObjects()
{
    std::cout << "[Place::generateObjects]"<<std::endl;
}

bool Place::enter(Character &character)
{
    // ** Remove player from previous place
    Place* old_place = character.currentPlace();
    if(old_place != nullptr)
        old_place->leave(character);

    // ** The character is now here
    this->characters_.push_back(&character);
    character.set_place(this);

    // ** Display the information
    display_information(character);
    return true;
}

bool Place::leave(Character &character)
{
    // ** Find character
    auto it = this->characters_.begin();
    for(Character* c : this->characters_)
    {
        if(c != nullptr && *c == character)
        {
            lab3::utils_io::print_newline("The character "+character.name()+" has left " + this->name_);
            // ** If found, remove from vector
            this->characters_.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

void Place::drop(Object &object)
{
    this->objects_.push_back(&object);
}

bool Place::pick_up(Object &object)
{
    // ** Find object
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

void Place::addDirection(const std::string &d, Place *p)
{
    this->directions_.insert(std::pair<std::string,Place*>(d,p));
}


Place &Place::neighbour(const std::string &direction)
{
    return *this->directions_.at(direction);
}


const std::map<std::string, Place*>& Place::directions() const
{
    return this->directions_;
}

const std::vector<Object *>& Place::objects() const
{
    return this->objects_;
}

const std::vector<Character*>& Place::characters() const
{
    return this->characters_;
}

void Place::display_information(const Character &character)
{
    std::cout << "\rThe character " << character.name()
              << " has entered the place '"<< this->name_ <<"'"<< std::endl;
    std::cout << description() << std::endl;
}

std::string Place::name() const     {return this->name_;}

std::string Place::description() const
{
    std::stringstream ss;

    // ** Display where you are
    ss << "You are at "<< name_<<std::endl;

    // ** Display objects
    if(this->objects_.size() > 0)
    {
        ss << "The following objects appear in the place: ";
        for(Object* o : this->objects_)
        {
            if(o != nullptr)
                ss << o->name() << ", ";
        }
        ss << std::endl;
    }
    else
        ss << "There are no objects here" << std::endl;

    // ** Display other characters
    if(this->characters_.size() > 0)
    {
        ss << "There are some characters in the place: ";
        for(Character* c : this->characters_)
        {
            if(c != nullptr)
                ss << c->name() <<", ";
        }
    }
    else
    {
        ss << "There are no characters here" << std::endl;
    }
    return ss.str();
}

void lab3::places::connectPlaces(Place &p1, Place &p2, const std::string &d12)
{
    auto oppositeDir = [&]() ->std::string
    {
        if(d12 == DIRECTION_EAST)
            return DIRECTION_WEST;
        else if(d12 == DIRECTION_NORTH)
            return DIRECTION_SOUTH;
        else if(d12 == DIRECTION_SOUTH)
            return DIRECTION_NORTH;
        else
            return DIRECTION_EAST;
    };

    p1.addDirection(d12, &p2);
    p2.addDirection(oppositeDir(), &p1);
}
