#include <utils/utils.h>

namespace lab3
{
namespace utils
{

std::string commonString(const std::vector<std::string> &v)
{
    // ** Get shortest string
    std::string minString;
    std::size_t minSize = -1;
    for(std::string s : v)
    {
        if(s.size() < minSize)
        {
            minSize = s.size();
            minString = s;
        }
    }
    // ** Loop over the chars and check if they are common to all the strings
    std::stringstream ss;
    for(std::size_t i = 0; i < minString.size(); ++i)
    {
        for(std::string s : v)
        {
            if(s.substr(0,ss.str().size()) != ss.str())
                return ss.str().substr(0,ss.str().size()-1);
        }
        char c = minString[i];
        ss << c;
    }

    return ss.str();
}

}
}


