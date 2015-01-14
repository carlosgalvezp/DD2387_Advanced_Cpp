#include <place.h>
using namespace lab3;

Place::Place(const std::string &name)
    : name_(name)
{
    place_commands_ =
    {
        CMD_GO,
        CMD_FIGHT,
        CMD_TALK,
        CMD_PICK_UP,
        CMD_DROP
    };
}

Place::~Place()
{
    // ** Delete objects
    for(Object* o : objects_)
    {
        if(o != nullptr)
        {
            delete o;
            o = nullptr;
        }
    }
}

const std::vector<std::string>& Place::getCommands() const {    return this->place_commands_;}

void Place::generateObjects()
{
    std::cout << "[Place::generateObjects]"<<std::endl;
}

void Place::addCharacter(Character &character)
{
    this->characters_.push_back(&character);
    character.set_place(this);
}

bool Place::enter(Character &character)
{
    // ** Remove player from previous place
    Place* old_place = character.currentPlace();
    if(old_place != nullptr)
        old_place->leave(character);

    // ** The character is now here
    this->addCharacter(character);

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
    for(auto it = this->objects_.begin(); it != this->objects_.end(); ++it)
    {
        if (**it == object)
        {
            this->objects_.erase(it);
            return true;
        }
    }
    return false;
}

void Place::addDirection(const std::string &d, Place *p)
{
    this->directions_.insert(std::pair<std::string,Place*>(d,p));
}

void Place::addObject(Object &o)
{
    this->objects_.push_back(&o);
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
        ss << "The following objects appear in the place: "<<std::endl;
        // ** Create unique names
        std::vector<std::string> unique_names;
        for(Object *o : this->objects())
        {
            if(o != nullptr && std::find(unique_names.begin(), unique_names.end(),o->name())==unique_names.end())
            {
                unique_names.push_back(o->name());
                ss << "  -"<<o->name() << std::endl;
            }
        }        
        ss << std::endl;
    }
    else
        ss << "There are no objects here" << std::endl;

    // ** Display other characters
    if(this->characters_.size() > 0)
    {
        ss << "There are some characters in the place: "<<std::endl;
        for(Character* c : this->characters_)
        {
            if(c != nullptr)
                ss << "  -"<<c->name() <<std::endl;
        }
    }
    else
    {
        ss << "There are no characters here" << std::endl;
    }
    return ss.str();
}

bool Place::operator ==(const Place &p2) const
{
    return this->name() == p2.name();
}

void Place::killCharacter(Character &character)
{
    this->leave(character);
    Character*c = &character;
    delete c;
    c = nullptr;
}

bool Place::containsCharacter(const std::string &character_name) const
{
    for(Character *c : this->characters_)
    {
        if(c->name() == character_name)
            return true;
    }
    return false;
}

Character* Place::getCharacter(const std::string &name)
{
    for(Character *c : this->characters_)
    {
        if(c->name() == name)
            return c;
    }
    return nullptr;
}


void lab3::places::connectPlaces(Place &p1, Place &p2, const std::string &d12)
{
    p1.addDirection(d12, &p2);
    p2.addDirection(lab3::utils::oppositeDirection(d12), &p1);
}

