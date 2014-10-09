#include <iostream>
#include "date.h"
#include "gregorian.h"
#include "julian.h"
#include "calendar.hpp"

using namespace lab2;

void test1();
void test2();
void test3();

void test4();
int main()
{
//    test1();
//    test2();
    test3();
//    test4();
    return 0;
}

void test1()
{
    Julian j;
    Gregorian g, g2;

    std::cout << "Gregorian: "<< g.mod_julian_day() << std::endl;
    std::cout << "Julian: " << j.mod_julian_day() << std::endl;

    std::cout << "Gregorian: "<< g << std::endl;
    std::cout << "Julian: "<<j << std::endl;


    std::cout << "Add month:" << g.add_month(5) << std::endl;
    for(int i = 0; i< 5; ++i)
        g2.add_month();
    std::cout << "Alternative add month: "<<g2 <<std::endl;
//    std::cout << "Add year:" << g.add_year() << std::endl;
    Gregorian g3(29,2,2014);
    g3.add_year();
    std::cout << "Add year: "<< g3<<std::endl;
    g3.add_year(-1);
    std::cout << "Add year: "<<g3 << std::endl;

    Gregorian g4(29,2,2004);
    g4.add_year(4);
    std::cout << "4 years: "<<g4<<std::endl;
}

void test2()
{
    std::cout << "----------------------------------------" << std::endl;
    Calendar<Gregorian> cal;
    cal.set_date(2000, 12, 2);
    cal.add_event("Basketträning", 4, 12, 2000);
    cal.add_event("Basketträning", 11, 12, 2000);
    cal.add_event("Nyårsfrukost", 1, 1, 2001);
    cal.add_event("Första advent", 1);
    // år = 2000, månad = 12
    cal.add_event("Vårdagjämning", 20, 3);
    // år = 2000
    cal.add_event("Julafton", 24, 12);
    cal.add_event("Kalle Anka hälsar god jul", 24); // också på julafton
    cal.add_event("Julafton", 24); // En likadan händelse samma datum ska
    // ignoreras och inte sättas in i kalendern
    cal.add_event("Min första cykel", 20, 12, 2000);
    cal.remove_event("Basketträning", 4);
    std::cout << cal; // OBS! Vårdagjämning och första advent är
    // före nuvarande datum och skrivs inte ut
    std::cout << "----------------------------------------" << std::endl;
    cal.remove_event("Vårdagjämning", 20, 3, 2000);
    cal.remove_event("Kalle Anka hälsar god jul", 24, 12, 2000);
    cal.set_date(2000, 11, 2);
    if (! cal.remove_event("Julafton", 24)) {
    std::cout << " cal.remove_event(\"Julafton\", 24) tar inte"<< std::endl
    << " bort något eftersom aktuell månad är november" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << cal;
}

void test3()
{
    Calendar<Gregorian> cal;
    cal.add_event("Tenta", 28, 10, 2014);
    cal.add_event("Flytta till Spanien", 30, 10, 2014);
    cal.add_event("Blabla", 31, 9, 2014);
//    cal.set_format(Calendar<Gregorian>::format::iCalendar);
    cal.set_format(Calendar<Gregorian>::format::cal);
    std::cout << cal;
}
