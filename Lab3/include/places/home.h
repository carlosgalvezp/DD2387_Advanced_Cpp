#ifndef HOME_H
#define HOME_H

#include <place.h>

namespace lab3
{
namespace places
{

class Home : public Place
{
public:
    Home();
    Home(const std::string &name);
    ~Home();
};
}
}


#endif // HOME_H
