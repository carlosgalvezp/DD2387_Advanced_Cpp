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

std::map<std::string, std::string> direction_pairs =
{
    {DIRECTION_NORTH, DIRECTION_SOUTH},
    {DIRECTION_SOUTH, DIRECTION_NORTH},
    {DIRECTION_EAST,  DIRECTION_WEST},
    {DIRECTION_WEST,  DIRECTION_EAST},
    {DIRECTION_NW,    DIRECTION_SE},
    {DIRECTION_NE,    DIRECTION_SW},
    {DIRECTION_SW,    DIRECTION_NE},
    {DIRECTION_SE,    DIRECTION_NW}
};
std::string oppositeDirection(const std::string &dir)
{
    return direction_pairs.at(dir);
}
}
}


