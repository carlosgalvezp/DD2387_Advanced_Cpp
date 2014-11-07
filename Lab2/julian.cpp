#include "julian.h"

namespace lab2
{

Julian::Julian()
{
    // Base already computed julian_day_, but date in Gregorian format -> convert
    date_from_julian(julian_day_, day_, month_, year_);
}

Julian::Julian(int year, int month, int day)
    :Date_impl(year, month, day)
{
    check_date(day, month, year);
    julian_day_ = julian_from_date(day, month, year);
}

Julian::Julian(const Date& src)
    :Date_impl(src)
{
    date_from_julian(julian_day_, day_, month_, year_);
}

Date& Julian::operator=(const Date& src)
{
    if(&src != this)
    {
        days_week_ = day_names_.size();
        months_year_ = month_names_.size();
        julian_day_ = src.mod_julian_day() + MOD_JULIAN_DATE_DIFF;
        date_from_julian(julian_day_, day_, month_, year_);
    }
    return *this;
}

Julian::~Julian(){}

bool Julian::is_leap_year(int year) const{return year % 4 == 0;}

void Julian::date_from_julian(double julian, int &day, int &month, int &year) const
{
    // ** From http://www.calendarhome.com/plugins/content/calendarhomecontent/converter/calendar.js
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
    // ** From http://www.calendarhome.com/plugins/content/calendarhomecontent/converter/calendar.js
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
