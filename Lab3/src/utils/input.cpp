#include <utils/input.h>

namespace lab3
{
namespace input
{

std::string read_input(const std::vector<std::string> &available_commands)
{
    std::stringstream ss;
    char c;
    bool correct_command(true);
    std::cout << "\r";
    display_commands(available_commands);
    do
    {
        system("stty raw");  // Avoid having to press Enter after each character
        c=getchar();

        if(c == '\t') // Tab completion     // Might as well use function pointers
        {
            if(ss.str().size() == 0)        // The player doesn't know what to do
            {
                display_commands(available_commands);
            }
            else
            {
                std::string s_found = tab_completion(ss.str(), available_commands);
                if(s_found != " ")
                    ss.str(s_found);
            }
        }
        else if(c == 127) // Backspace
        {
            std::string new_str = ss.str().substr(0, ss.str().size()-1);
            ss.str("");
            ss << new_str;
        }
        else if(c == '\r') // Enter
        {
            if(std::find(available_commands.begin(), available_commands.end(), ss.str()) == available_commands.end())
            {
                ss.str("");
                correct_command = false;
                lab3::utils_io::print_newline("Incorrect command, please try again");
            }
            else
                correct_command = true;
        }
        else
        {
            ss << c;
        }
        std::cout << "\r" << "                               "; // Remove garbage printed from backspace or enter
        std::cout << "\r" << ">> "<<ss.str();
    }
    while (c != '\r' || !correct_command);
    std::cout << "\r" << ">> "<<ss.str()<<std::endl;
    system("stty cooked");  // Restore original config
    return ss.str();
}

std::string tab_completion(const std::string &tmp_str, const std::vector<std::string> &available_commands)
{
    int n_found = 0;
    std::string s_found = " ";
    std::stringstream ss;
    for(std::string s : available_commands)
    {
        if(s.substr(0,tmp_str.size()) == tmp_str) // Found
        {
            ++n_found;
            s_found = s;
            ss << "\r" << s << std::endl;
        }
    }
    if(n_found != 1)
    {
        std::cout << ss.str();
        s_found = " ";
    }

    return s_found;
}

void display_commands(const std::vector<std::string> &commands)
{
    lab3::utils_io::print_newline("--- Available commands ---");
    for(std::string s : commands)
        lab3::utils_io::print_newline(s);

}

void wait_for_enter()
{
    lab3::utils_io::print_newline("Press Enter to continue...");
    getchar();
}

}
}

