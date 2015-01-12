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

void wait_for_enter()
{
    lab3::utils_io::print_newline("\nPress Enter to continue...");
    getchar();
}

}
}
