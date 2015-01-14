#include "object.h"

using namespace lab3;

Object::Object(const std::string &name, const std::string &description, int price, int volume, int weight)
    : name_(name),
      description_(description),
      price_(price),
      volume_(volume),
      weight_(weight)
{}

Object::~Object(){}

// ** Accessors
std::string Object::name()        const { return this->name_; }
int Object::volume()              const { return this->volume_;}
int Object::price()               const { return this->price_;}
int Object::weight()              const { return this->weight_;}


std::string Object::description()           const
{
    std::stringstream ss;
    ss << this->description_
       << ". Price: "  << this->price()
       <<  " Volume: " << this->volume()
       <<  " Weight: " << this->weight();
    return ss.str();
}

bool Object::operator ==(const Object& o)   const
{
    return o.name() == this->name() &&
           o.volume() == this->volume() &&
           o.weight() == this->weight();
}
