#include "safe_vector.hpp"
#include <assert.h>             // assert(b) ger felmeddelande om b falsk
#include <thread>
#include <exception>
#include <vector>

// Big struct so that it takes time to process it => easy to see deadlocks
struct A
{
    std::vector<int> v1,v2,v3;
    A()
    {
        v1.resize(1000000);
        v2.resize(1000000);
        v3.resize(1000000);
    }

};

void swap_function(SafeVector<A> *v, std::size_t idx1, std::size_t idx2);


std::ostream& operator<<(std::ostream& os, A& a)
{
    return os;
}


int main()
{
    // ** Create SafeVector
    A a,b,c,d,e,f,g;
    SafeVector<A> v({a,b,c,d,e,f,g});
    v.print();

    // ** Create and run threads. NOTE: if either of them throws an exception, everything crashes
    std::thread th1 (swap_function, &v, 2, 3);
    std::thread th2 (swap_function, &v, 3, 2);

    // ** Wait for the threads to finish
    th1.join();
    th2.join();

    // ** Print resulting vector
    v.print();
    return 0;
}

void swap_function(SafeVector<A> *v, std::size_t idx1, std::size_t idx2)
{
    v->safeswap2(idx1, idx2);
}
