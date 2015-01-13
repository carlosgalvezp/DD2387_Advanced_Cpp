#ifndef UTILS_H
#define UTILS_H

// STL
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <map>

#include <names.h>
namespace lab3
{
namespace utils
{

std::string commonString(const std::vector<std::string> &v);
std::string oppositeDirection(const std::string &dir);

// Random
double fRand(double fMin = 0.0, double fMax = 1.0);
int rollDice();
bool eventHappens(double prob);

std::string getRandomCommandPoints(const std::vector<std::string> &commands, const std::vector<int>&    commandPoints);
std::string getRandomCommandProbs(const std::vector<std::string> &commands, const std::vector<double>& commandProbs);

}

}


#endif // UTILS_H
