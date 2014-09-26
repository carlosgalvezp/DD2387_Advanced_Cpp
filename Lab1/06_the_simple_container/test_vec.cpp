#include <iostream>
#include <stdexcept>
#include "kth_cprog_simple_container.hpp"     // inkludera din headerfil har

//int main()
//{
//    UIntVector v(5);
//    unsigned int a = v[2];
//    std::cout<<"Value "<<a<<std::endl;
//    try{
//    unsigned int b = v[10];
//    }catch (std::out_of_range e){
//        std::cout<<e.what();
//    }

//    v[1] = 10;
//    a = v[3];
//    a = 7;
//    std::cout<<"Changed: "<<v[1]<<" Not changed: "<<v[3]<<std::endl;

//    UIntVector v2(v);
//    v2[1] = 33;
//    std::cout<<"New vector: "<<v2[1] << ", old one: "<<v[1] << std::endl;

//    // Test initializer list
//    UIntVector v3({1,5,7,8});
//    std::cout<<"Initializer list: "<<v3[2]<<std::endl;

//    // Test copy-assignment operator
//    UIntVector v4;
//    v4= v3;
//    v4[1] = 77;
//    std::cout<<"Copy-assignment: "<<v3[1] << ", "<<v4[1]<<std::endl;
//    return 0;
//}

int main()
{
    // Nagra saker som ska fungera:
    UIntVector a(7);           // initiering med 7 element
    UIntVector b(a);           // kopieringskonstruktor
    UIntVector c = a;          // kopieringskonstruktor

    a = b;                 // tilldelning genom kopiering
    a[5] = 7;              // tilldelning till element

    const UIntVector e(10);    // konstant objekt med 10 element
    int i = e[5];          // const int oper[](int) const kors
    i = a[0];              // vektorn ar nollindexerad
    i = a[5];              // int oper[](int) kors

    a[5]++;                // oka vardet till 8

    try {
        i = e[10];             // forsoker hamta element som ligger utanfor e
    } catch (std::out_of_range e) {
        std::cout << e.what() << std::endl;
    }

#if 0
    // Diverse saker att testa
    e[5] = 3;              // fel: (kompilerar ej) tilldelning till const
    b = b;                 // hmm: se till att inte minnet som skall behallas frigors
#endif

    UIntVector f(0);
    return 0;
}

