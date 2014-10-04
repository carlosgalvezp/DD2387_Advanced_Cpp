#include "kth_cprog_template_container2.hpp"             // inkludera din headerfil har
#include <assert.h>             // assert(b) ger felmeddelande om b falsk
#include <vector>
void test_kth();

void test_reset();
void test_push();
void test_insert();
void test_clear();
void test_erase();
void test_capacity();
void test_iterators();
void test_find();
void test_operators();

void test_bug();
void test_kth();

void test_master();

struct T1 {
    T1 () {std::cout << "Default constructor" << std::endl; ++object_count; }
    T1 (T1 const&){ std::cout << "Copy constructor" << std::endl; ++object_count; }
    ~T1 () {std::cout << "Destructor" << std::endl; --object_count; }
    static unsigned int object_count;
};

unsigned int T1::object_count = 0;


int main()
{
//    test_kth();
//    test_reset();
//    test_push();
//    test_insert();
//    test_clear();
//    test_erase();
//    test_bug();
//    test_operators();
    test_master();
    return 0;
}

void test_master()
{
    {
        Vector<T1> v1 (3); assert (T1::object_count == 3 && v1.capacity () >= 3);
        Vector<T1> v2; assert (T1::object_count == 3);
        v1.push_back (T1{}); assert (T1::object_count == 4 && v1.capacity () >= 4);
        v2 = v1; assert (T1::object_count == 8);
        v2.erase (1); assert (T1::object_count == 7);
        v2.erase (1); assert (T1::object_count == 6);
        v1.reset();
    }
    assert (T1::object_count == 0);

}

void test_kth()
{
    Vector<double> v;           // ok: defaultkonstruktor ger vektor med flyttal
    Vector<char> *a = new Vector<char>[3];  // dynamiskt allokerade ser ut sa har
    delete [] a;

    assert(v.size() == 0);      // tom fran borjan
    v.push_back(3.14);          // lagg till ett element sist
    v.print();
    assert(v.size() == 1);      // nu ligger ett element i vektorn
    v.insert(0, 2.10);          // lagg till fore element 0, dvs forst
    v.print();
    assert(v[0] == 2.10 &&      // hamnade de ratt?
       v[1] == 3.14);
    assert(v.size() == 2);      // nu ligger tva element i vektorn

    v.reset();
    std::cout<< "Getting begin..." << std::endl;
    auto asd = v.begin();
    std::cout << "Getting end..."<< std::endl;
    auto bad = v.end();
    std::cout << "Finished"<<std::endl;
    assert(bad > asd);

    v.erase(0);                 // ta bort forsta elementet
    assert(v.size() == 1);      // ratt antal elelment
    v.clear();                  // tom hela vektorn
    assert(v.size() == 0);      // tom nar alla element ar borttagna

//    // kontrollera att foljande rader inte gar att kompilera
//    vc[0] = 3.1415;             // fel: tilldelning av konstant objekt
//    Vector<char> c = v;         // fel: tilldelning av olika typer
}

void test_reset()
{
    std::cout << "test_reset()...";
    // Reset normal vector
    Vector<double> v({3.4, 5.7, 2.4, 9.5});
    v.reset();
    for(std::size_t i = 0; i< v.size(); ++i)
        assert(v[i] == 0.0);

    // Reset zero-elements vector
    Vector<double> v2;
    v2.reset();
    std::cout << "ok" << std::endl;
}

void test_push()
{
    std::cout << "test_push()...";
    // Create zero-vector and push
    Vector<double> v;
    v.push_back(0.2);
    assert(v[0] == 0.2);
    assert(v.size() == 1);
    v.push_back(2.4);
    assert(v.size() == 2);

    // Create non-zero vector and push
    Vector<double> v2 = v;
    v2.push_back(0.7);
    assert(v2.size() == 3);
    std::cout << "ok" << std::endl;
}

void test_insert()
{
    std::cout << "test_insert()...";

    Vector<int> a;
    a.insert(0,42); a.print();
    a.insert(0,-43); a.print();
    a.insert(1,44); a.print();
    a.insert(3,45); a.print();
    a.insert(0,42); a.print();

    // Normal behaviour
//    assert(v[0] == 0);
//    assert(v.size() == 5);

//    // Insert at invalid indices
//    Vector<int> v2 = v;
//    try
//    {
//        v2.insert(-1, 3);
//    }
//    catch(std::exception& e)
//    {
//        std::cout << e.what() << std::endl;
//    }

//    try
//    {
//        v2.insert(v2.size()+1, 3);
//    }
//    catch(std::exception& e)
//    {
//        std::cout << e.what() << std::endl ;
//    }
//    v2.insert(v2.size(), 9);
////    v2.print();

//    // Insert when zero-element
//    Vector<int> v3, v4;
//    v3.insert(0,1);
//    assert(v3[0] == 1);
//    assert(v3.size() == 1);

//    try{
//        v4.insert(1,1);
//    }
//    catch(std::exception& e){std::cout << e.what() << std::endl;}

//    // Insert when one-element
//    Vector<int> v5({1}), v6({1}), v7({1});
//    v5.insert(0,2);
//    v5.print();
//    v6.insert(1,4);
//    v6.print();
//    try{
//        v7.insert(2,5);
//    }catch(std::exception& e){std::cout << e.what() << std::endl;}
//    std::cout << "Inserting..."<<std::endl;
//    v5.insert(2,5);
//    v5.print();
    std::cout << "ok" << std::endl;
}

void test_clear()
{
    std::cout << "Test clear...";
    // Normal vector
    Vector<int> v({1,2,3,4,5});
    v.clear();
    assert(v.size() == 0);

    // Zero-vector
    Vector<int> v2;
    v2.clear();
    assert(v2.size() == 0);

    std::cout << "ok" << std::endl;
}

void test_erase()
{
    std::cout << "Test erase... ";
    // Normal vector
    Vector<int> v({1,2,3,4,5});
    v.erase(0);
    v.print();
    v.erase(v.size()-1);
    v.print();

    try{
       v.erase(3);
       v.print();
    }catch(std::exception& e){std::cout << e.what() << std::endl;}

    Vector<int> v2({1});
    Vector<int> v3 = v2, v4 = v2;
    v2.erase(0);
    try{
        v3.erase(1);
    }catch(std::exception& e){std::cout << e.what() << std::endl;}
    try{
        v4.erase(2);
    }catch(std::exception& e){std::cout << e.what() << std::endl;}
    std::cout << "ok" << std::endl;
}


void test_bug()
{
    Vector<int> v({1});
    v.clear();
    v.push_back(1);
}

void test_operators()
{
    Vector<int> v({1,2,3});
    v.print();
    v[0] = 5;
    v.print();
    int a = v[2];
    a = 77;
    v.print();
}
