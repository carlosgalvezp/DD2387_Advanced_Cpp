#ifndef INDOOR_H
#define INDOOR_H

#include <place.h>

namespace lab3
{
namespace places
{

class Indoor : public Place
{
public:
    Indoor();
    Indoor(const std::string &name, bool is_open);
    bool isOpen()   const;
    void open();

    ~Indoor();
private:
    bool is_open_;
};

}
}

#endif // INDOOR_H
