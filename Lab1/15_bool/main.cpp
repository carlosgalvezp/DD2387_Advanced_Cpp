#include "bool_vector.hpp"
#include <vector>
#include <algorithm>
#include <type_traits>

void f(int x);

void testReference();
void testKTH();
void testMove();
void testSwap();
void testIntConversion();

int main()
{
//    testReference();
//    testKTH();
//    testMove();
//    testSwap();
    testIntConversion();
    return 0;
}

void testSwap()
{
    // ** Swap vectors
    Vector<bool> v1(31);
    v1[3] = v1[5] = 1;
    Vector<bool> v2(31);

    std::cout << "v1\n";
    v1.print();
    std::cout << "v2\n";
    v2.print();

    std::cout << "Swapping v1 and v2"<<std::endl;
    std::swap(v1, v2);
    std::cout << "v1\n";
    v1.print();
    std::cout << "v2\n";
    v2.print();

    // ** Swap references and iterators
    Vector<bool>::iterator it1(Vector<bool>::reference(&v2,3));
    Vector<bool>::iterator it2(Vector<bool>::reference(&v2,0));

    swap(*it1, *it2);
    std::cout << "Swapped dereference of v2 at positions 0 and 3"<<std::endl;
    v2.print();

    std::iter_swap(it1, it2);
    std::cout << "Swapped iterators of v2 at positions 0 and 3"<<std::endl;
    v2.print();
}

void testMove()
{
    std::cout << "Vector<bool>::reference is MoveAssignable? ";
    std::cout << std::is_move_assignable<Vector<bool>::reference>::value<<std::endl;

    std::cout << "Vector<bool>::const_reference is MoveAssignable? ";
    std::cout << std::is_move_assignable<Vector<bool>::const_reference>::value<<std::endl;

    std::cout << "Vector<bool>::reference is MoveConstructible? ";
    std::cout << std::is_move_constructible<Vector<bool>::reference>::value<<std::endl;

    std::cout << "Vector<bool>::const_reference is MoveConstructible? ";
    std::cout << std::is_move_constructible<Vector<bool>::const_reference>::value<<std::endl;

}

void testReference()
{
    Vector<bool> v(31);
    Vector<bool>::reference r(&v, 1);
    std::cout << "Before: "<<std::endl;
    v.print();
    r = true;
    std::cout << "After: " <<std::endl;
    v.print();

    // Test const
//    Vector<bool>::const_reference r2(&v, 3);
    Vector<bool>::reference r2(&v, 3);

    r2 = true;
}

void testKTH()
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
    v.print();
}

void testIntConversion()
{
    Vector<bool> v(10);
    v[5] = true;

    std::cout << "Vector to int"<<std::endl;
    v.print();
    std::cout << vectorToInt(v)<<std::endl;

    std::cout << "Int to vector" <<std::endl;
    int n = 1133;
    Vector<bool> v2 = intToVector(n);
    std::cout << "N = "<<n<<std::endl;
    v2.print();
}

