#include <places/castle.h>
#include <objects/container.h>

using namespace lab3::places;
using namespace lab3;

Castle::Castle()
{}

Castle::Castle(const std::string &name, bool is_open)
    : Indoor(name, is_open)
{}

Castle::~Castle()
{}

bool Castle::enter(Character &character)
{
    // ** Check for the key
    if(!this->isOpen())
    {
        for(Object*o : character.objects())
        {
            // Look inside containers
            objects::Container *o_container = dynamic_cast<lab3::objects::Container*>(o);
            if(o_container != nullptr)
            {
                for(Object *item : o_container->objects())
                {
                    if(item->name() == "key" )
                    {
                        this->is_open_ = true;
                        lab3::utils_io::print_newline("The King's Castle is closed, but you open it with the key...");
                        return Indoor::enter(character);
                    }
                }
            }
        }
    }
    return Indoor::enter(character);
}

