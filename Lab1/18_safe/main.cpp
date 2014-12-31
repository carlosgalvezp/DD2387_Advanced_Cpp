#include "safe_vector.hpp"
#include <vector>
#include <algorithm>
#include <type_traits>

template<typename T>
bool vectorEquals(const SafeVector<T> &v1, const SafeVector<T> &v2);

void test1();
void test2();
void test3();

int main()
{
//    test1();
//    test2();

    try
    {
        test3();
    }catch(std::exception &e){}

    return 0;
}

void test1()
{
    SafeVector<int> v1(20);
    v1[0] = 213;
    v1[7] = 4436;
    v1[12] = 123;
    SafeVector<int> v1_copy(v1);

    try
    {
        v1 = SafeVector<int>(1000000000);
    }
    catch(std::exception &e)
    {
        std::cout << "Exception: "<<e.what() << std::endl;

        // Check that v1 is still the same
        std::cout << "Equal vectors: "<<(vectorEquals(v1,v1_copy))<<std::endl;
        return;
    }
    std::cout << "No exception" << std::endl;
}

void test2()
{
    SafeVector<int> v1(200000000);
    SafeVector<int> v1_copy;

    // ** Push until fail
    for(std::size_t i= 0; i < 1000000000; ++i)
    {
        try
        {
            std::cout << "Pushing "<<i<<std::endl;
            v1.push_back(i);
        }
        catch(std::exception &e)
        {
            std::cout << "Exception when pushing "<<i<<": "<<e.what()<<std::endl;
            std::cout << "Equal vectors: "<<vectorEquals(v1,v1_copy) << std::endl;
            return;
        }

        // Backup data
        v1_copy = v1;
    }
    std::cout << "No exception" << std::endl;
}

void test3()
{
    SafeVector<int> v1(1000);
    std::cout << "Throwing exception" << std::endl;
    throw std::out_of_range("Throwing exception..."); // The vector will be destroyed even with this
}


template<typename T>
bool vectorEquals(const SafeVector<T> &v1, const SafeVector<T> &v2)
{
    if(v1.capacity() != v2.capacity()) return false;
    if(v1.size() != v2.size()) return false;

    for(std::size_t i = 0; i < v1.size(); ++i)
    {
        if(v1[i] != v2[i])
            return false;
    }
    return true;
}
