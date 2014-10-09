#include "julian.h"

namespace lab2
{

Julian::Julian()
{
    date_from_julian(julian_day_, day_, month_, year_); // Base already computed julian_day_
}

Julian::Julian(int day, int month, int year)
    :Date_impl(day, month, year)
{
    julian_day_ = julian_from_date(day, month, year);
}

Julian::Julian(int day, int month, int year, const std::vector<std::string>& day_names,
                                             const std::vector<std::string>& month_names)
    :Date_impl(day, month, year, day_names, month_names)
{
    julian_day_ = julian_from_date(day, month, year);
}

Julian::~Julian(){}

bool Julian::is_leap_year(int year) const{return year % 4 == 0;}

void Julian::date_from_julian(double julian, int &day, int &month, int &year) const
{
    double z, a, b, c, d, e;
    double td = julian;

    td += 0.5;
    z = floor(td);

    a = z;
    b = a + 1524;
    c = floor((b - 122.1) / 365.25);
    d = floor(365.25 * c);
    e = floor((b - d) / 30.6001);

    month = floor((e < 14) ? (e - 1) : (e - 13));
    year = floor((month > 2) ? (c - 4716) : (c - 4715));
    day = b - d - floor(30.6001 * e);

    if (year < 1) {
        year--;
    }
}

double Julian::julian_from_date(int day, int month, int year) const
{
    if (year < 1) {
        year++;
    }
    if (month <= 2) {
        year--;
        month += 12;
    }

    return ((floor((365.25 * (year + 4716))) +
            floor((30.6001 * (month + 1))) +
            day) - 1524.5);
}
} // namespace lab2
