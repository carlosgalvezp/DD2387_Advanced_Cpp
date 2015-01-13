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

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int rollDice()
{
    return (rand() % 6 + 1);
}

bool eventHappens(double prob)
{
    return prob >= fRand();
}

std::string getRandomCommandProbs(const std::vector<std::string> &commands, const std::vector<double>& commandProbs)
{
    // ** Create cumulative sum
    std::vector<double> cum_sum(commandProbs.size());
    for(std::size_t i = 0; i < commandProbs.size(); ++i)
    {
        cum_sum[i] = cum_sum[std::max(0,(int)i-1)] + commandProbs[i];
    }

    // ** Get command
    double r = fRand();
    for(std::size_t i = 0; i < cum_sum.size(); ++i)
    {
        if(cum_sum[i] >= r)
            return commands[i];
    }
    return "";
}

std::string getRandomCommandPoints(const std::vector<std::string> &commands, const std::vector<int>& commandPoints)
{
    // ** Compute probabilities
    std::vector<double> commandProbs(commandPoints.size());
    int maxPoints(0);
    for(int p : commandPoints)
    {
        maxPoints += p;
    }

    for(std::size_t i = 0; i < commandPoints.size(); ++i)
    {
        commandProbs[i] = (double)commandPoints[i] / (double)maxPoints;
    }

    // ** Get command from probabilities
    return getRandomCommandProbs(commands, commandProbs);
}


}
}
