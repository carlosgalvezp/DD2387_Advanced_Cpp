#include <places/indoor.h>
#include <characters/human.h>
using namespace lab3::places;
using namespace lab3;

Indoor::Indoor()
{}

Indoor::Indoor(const std::string &name, bool is_open)
    : Place(name), is_open_(is_open)
{}


Indoor::~Indoor()
{}

bool Indoor::isOpen() const {return this->is_open_;}

void Indoor::setOpen(bool open){ this->is_open_ = open;}

bool Indoor::enter(Character &character)
{
    // ** Check if door open
    if(this->isOpen())
    {
        return Place::enter(character);
    }
    else
    {
        characters::Human* c_human = dynamic_cast<characters::Human*>(&character);
        if(c_human == nullptr) // Not a human
        {
            return false;
        }

        // ** See if you have the key to the place
        for(Object*o : character.objects())
        {
            objects::Key *found_key = nullptr;
            objects::Container *o_container = dynamic_cast<lab3::objects::Container*>(o);
            objects::Key    *o_key          = dynamic_cast<lab3::objects::Key*>(o);

            // Look inside containers
            if(o_container != nullptr)
            {
                for(Object *item : o_container->objects())
                {
                    // Try to cast to key
                    objects::Key* key = dynamic_cast<objects::Key*>(item);
                    if(key != nullptr && isValidKey(*key))
                    {
                        found_key = key;
                    }
                }
            }
            else if(o_key != nullptr && isValidKey(*o_key)) { found_key = o_key;}

            if(found_key != nullptr)
            {
                this->is_open_ = true;
                std::stringstream ss;
                ss << ">>> The "<<this->name()<<"is closed, but you open it with the key <<<";
                lab3::utils_io::print_newline(ss.str());
                return Place::enter(character);
            }
        }

        lab3::utils_io::print_newline("You cannot enter the "+this->name()+", since it's closed.");
        return false;
    }
}

bool Indoor::isValidKey(const objects::Key &key) const
{
    return *key.getPlace() == *this;
}
