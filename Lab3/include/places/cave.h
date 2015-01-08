#ifndef CAVE_H
#define CAVE_H

#include <places/outdoor.h>

namespace lab3
{
namespace places
{

class Cave : public Outdoor
{
public:
    Cave();
    Cave(const std::string &name);

    void generateObjects();

    ~Cave();
};

}
}


#endif // CAVE_H
