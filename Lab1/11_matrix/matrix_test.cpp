#include "Matrix.h"

int main()
{
    Matrix a(10,10);
    Matrix b(a);
    Matrix c = a;
    c = b;

    Matrix x(2,2);
    x[0][0] = 3;
    x[0][1] = 2;
    x[1][0] = 7;
    x[1][1] = 8;

    Matrix y = x*5;
    Matrix z = -x;
    std::cout << "TEST"<<std::endl;
    std::cout << x << std::endl;
    std::cout << y << std::endl;

    std::stringstream stream("  [ 1 -7123 ; 0 2 ; 9 7 ]");
    Matrix m;
    stream >> m;
    std::cout << m;
    return 0;
}
