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

    std::cout << v.end() - v.begin() << std::endl;

    Vector<bool> w; // tom vektor
    std::copy(v.begin(), v.end(), std::back_inserter(w));
    w.print();
    std::cout << std::distance(v.begin(), v.end());
    Vector<bool>::const_iterator it = v.begin();
    std::advance(it, 2);

//    std::sort(v.begin(), v.end());
    return 0;
}

