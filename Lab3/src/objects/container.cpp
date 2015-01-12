#include <objects/container.h>

using namespace lab3::objects;

Container::Container()
{}

Container::Container(const std::string &name,
                     int price,
                     int volume,
                     int weight,
                     int max_volume,
                     int max_weight)
    : Object(name, "It contains objects", price, volume, weight),
      max_hold_weight_(max_weight),
      max_hold_volume_(max_volume),
      current_hold_weight_(0),
      current_hold_volume_(0)
{}

Container::~Container()
{
    for(Object *o : objects_)
    {
        if(o != nullptr)
        {
            delete o;
            o = nullptr;
        }
    }
}

bool Container::add(Object &object)
{
    if(current_hold_volume() + object.volume() > max_hold_volume()) // XXX Might as well use lambda function
    {
        std::stringstream ss;
        ss << "You cannot put the " << object.name() << " in the "+this->name()
           << " because the current hold volume is " << this->current_hold_volume()
           << " , the object volume is " << object.volume()
           << " and the maximum hold volume is " << max_hold_volume();
        lab3::utils_io::print_newline(ss.str());
        return false;
    }
    else if(current_hold_weight() + object.weight() > max_hold_weight())
    {
        std::stringstream ss;
        ss << "You cannot put the " << object.name() << " in the "+this->name()
           << " because the current hold weight is " << this->current_hold_weight()
           << " , the object weight is " << object.weight()
           << " and the maximum hold weight is " << max_hold_weight();
        lab3::utils_io::print_newline(ss.str());
        return false;
    }

    else // Everything alright
    {
        this->objects_.push_back(&object);
        this->current_hold_volume_ += object.volume();
        this->current_hold_weight_ += object.weight();

        std::stringstream ss;
        ss << "You have just added a " <<object.name() <<" into your "<<this->name() <<".\n"
           << "Now the current hold weight is "<<this->current_hold_weight()<<"/"<<this->max_hold_weight()
           << " and the current hold volume is "<<this->current_hold_volume()<<"/"<<this->max_hold_volume();
        lab3::utils_io::print_newline(ss.str());
        return true;
    }
}

bool Container::remove(const Object &object)
{
    auto it = this->objects_.begin();
    for(Object* o : this->objects_)
    {
        if (*o == object)
        {
            this->objects_.erase(it);
            this->current_hold_volume_ -= object.volume();
            this->current_hold_weight_ -= object.weight();

            std::stringstream ss;
            ss << "You have just removed a " <<object.name() <<" from your "<<this->name() <<".\n"
               << "Now the current hold weight is "<<this->current_hold_weight()<<"/"<<this->max_hold_weight()
               << " and the current hold volume is "<<this->current_hold_volume()<<"/"<<this->max_hold_volume();
            lab3::utils_io::print_newline(ss.str());
            return true;
        }

    }
    std::stringstream ss;
    ss << "You do not have a "<<object.name()<< " in your " << this->name()<<", so you cannot remove it";
    lab3::utils_io::print_newline(ss.str());
    return false;
}


// ** Accessors
int Container::current_hold_volume() const {return this->current_hold_volume_;}
int Container::current_hold_weight() const {return this->current_hold_weight_;}
int Container::max_hold_volume()     const {return this->max_hold_volume_;}
int Container::max_hold_weight()     const {return this->max_hold_weight_;}

const std::vector<lab3::Object*> &Container::objects() const{return this->objects_;}

std::string Container::description()    const
{
    std::stringstream ss;
    ss << "[Container] Hold Volume: "<< this->current_hold_volume()<<"/"<<this->max_hold_volume()
                    <<" Hold Weight: "<< this->current_hold_weight()<<"/"<<this->max_hold_weight();
    // ** Display container's objects
    for(Object *item : this->objects())
    {
        ss   <<std::endl     << "   - "      <<item->name()
                             << ". Price: " << item->price()
                             << " Volume: " << item->volume()
                             << " Weight: " << item->weight();
    }
    return ss.str();
}

bool Container::operator >(const Container &obj)    const
{
    return this->max_hold_volume() > obj.max_hold_volume() &&
           this->max_hold_weight() > obj.max_hold_weight();
}

bool Container::isMovableTo(const Container &c) const
{
    return c.max_hold_volume() >= this->current_hold_volume() &&
           c.max_hold_weight() >= this->current_hold_weight();
}

bool Container::moveObjectsTo(Container &c)
{
    if(this->isMovableTo(c))
    {
        // Move objects to the new container
        for(Object *o : this->objects_)
            c.add(*o);

        // Clear the current container
        this->objects_.clear();
        lab3::utils_io::print_newline("The contents of the "+this->name()+" have been moved to the "+c.name());
        return true;
    }
    else
    {
        lab3::utils_io::print_newline("The "+c.name()+" cannot hold all the objects in the "+this->name());
        lab3::utils_io::wait_for_enter();
        return false;
    }
}
