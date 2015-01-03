#include "object.h"

using namespace lab3;
Object::Object()
{}

Object::Object(const std::string &name)
    : name_(name)
{}

Object::~Object(){}

std::string Object::name() const { return this->name_; }

