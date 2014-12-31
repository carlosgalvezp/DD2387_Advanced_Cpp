#ifndef UI_OPTION_H
#define UI_OPTION_H

#include <string>

namespace lab3
{
namespace utils
{

struct UI_Option
{
    UI_Option(const std::string &name, const char key);

    std::string name_;
    char key_;
};

}
}

#endif // UI_OPTION_H
