#include "vector.h"             // inkludera din headerfil har
#include <assert.h>             // assert(b) ger felmeddelande om b falsk


int main()
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
//    v.sort(false);              // sortera i fallande ordning
//    assert(v[0] == 3.14 &&      // hamnade de ratt?
//       v[1] == 2.10);
//    assert(v.size() == 2);      // ingenting andrat?
//    v[1] = 2.11;                // tilldelning av enstaka element;

//    const Vector<double> &vc = v;  // skapa konstant referens
//    assert(vc.size() == 2);     // ok: andrar ej vektorn som ar konstant
//    assert(vc[0] == 3.14 &&     // ok: andrar ej vektorn som ar konstant
//       vc[1] == 2.11);
    
    v.erase(0);                 // ta bort forsta elementet
    assert(v.size() == 1);      // ratt antal elelment
    v.clear();                  // tom hela vektorn
    assert(v.size() == 0);      // tom nar alla element ar borttagna
    
    
//    // kontrollera att foljande rader inte gar att kompilera
//    vc[0] = 3.1415;             // fel: tilldelning av konstant objekt
//    Vector<char> c = v;         // fel: tilldelning av olika typer

//    return 0;
}
