#ifndef PRINCESS_H
#define PRINCESS_H

#include <characters/human.h>
#include <utils/utils_io.h>

namespace lab3
{
namespace characters
{
class Princess : public Human
{
public:
    Princess();
    Princess(const std::string& name, Place *place);
    ~Princess();

    bool action();
    std::string type() const;
};

}
}

#endif // PRINCESS_H
