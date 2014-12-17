#include "hypercube.hpp"

void testExample();

int main()
{
  testExample();
  return 0;
}

void testExample()
{
    Hypercube<3> n(7);
    Hypercube<6> m(5);
    m[1][3][2][1][4][0] = 7;

    Hypercube<3> t(5);
    t = m[1][3][2];
    t[1][4][0] = 2;

    std::cout << m[1][3][2][1][4][0] << std::endl;// 7
    std::cout << t[1][4][0] << std::endl;         // 2
}
