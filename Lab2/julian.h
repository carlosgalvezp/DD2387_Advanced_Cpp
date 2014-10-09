#ifndef JULIAN_H
#define JULIAN_H

#include "date.h"

namespace lab2
{

class Julian : public Date_impl
{
public:
    Julian();
    Julian(int day, int month, int year);
    Julian(int day, int month, int year, const std::vector<std::string>& day_names,
                                         const std::vector<std::string>& month_names);
    ~Julian();

private:
    bool is_leap_year(int year) const;
    void date_from_julian(double julian, int &day, int &month, int &year) const;
    double julian_from_date(int day, int month, int year) const;
};


} // namespace lab2

#endif // JULIAN_H
