#include <utils/utils.h>

namespace lab3
{
namespace utils
{

void displaySelectionMenu(const std::vector<UI_Option> &options)
{
    for(std::size_t i = 0; i < options.size(); ++i)
    {
        const UI_Option &o = options[i];
        std::stringstream ss;
        ss << "["<<o.key_<<"] "<<o.name_;
        std::cout << ss.str() << std::endl;
    }
}

int readKeyboardInput(const std::vector<UI_Option> &options)
{
    // ** Get char from keyboard
    system("stty raw");         // Avoid pressing Enter
    char c = getchar();
    system("stty cooked");      // Restore default config
    std::cout << std::endl; // After the pressed key
    for(std::size_t i = 0; i < options.size(); ++i)
    {
        if(c == options[i].key_)
            return i;
    }
    return -1;
}

}
}


