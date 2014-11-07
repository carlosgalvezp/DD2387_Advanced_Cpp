#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "date.h"

namespace lab2
{

class Gregorian : public Date_impl
{
public:
    Gregorian();
    Gregorian(const Date& src);
    Date& operator=(const Date& src);
    Gregorian(int day, int month, int year);
    ~Gregorian();

private:
    bool is_leap_year(int year)                                           const;
    double julian_from_date(int day, int month, int year)                 const;
    void date_from_julian(double julian, int &day, int &month, int &year) const;
};

}

#endif // GREGORIAN_H
