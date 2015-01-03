#include <utils/utils_io.h>

namespace lab3
{
namespace utils_io
{
void print_newline(const std::string &s)
{
    std::cout << "\r" << s << std::endl;
}

void clearScreen()
{
    system("clear");
}

}
}
