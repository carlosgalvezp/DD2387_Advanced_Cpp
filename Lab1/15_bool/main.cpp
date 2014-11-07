#include "bool_vector.hpp"
#include <vector>
#include <algorithm>
void f(int x);

int main()
{
    Vector<bool> v(31); // Skapa en 31 stor vektor
    v[3] = true;
    v[0] = true;
    v[5] = v[7] = true;
    v.print();

    std::cout << "SUBTRACTION: " <<v.end() - v.begin() << std::endl;

    Vector<bool> w; // tom vektor
    std::copy(v.begin(), v.end(), std::back_inserter(w));
    w.print();

    std::cout << "STD::DISTANCE " << std::distance(v.begin(), v.end())<<std::endl;
    Vector<bool>::iterator it = v.begin();
    std::cout << *it<< std::endl;
    std::advance(it, 2);
    std::cout << *it << std::endl;

    std::sort(v.begin(), v.end());
    return 0;
}

