#include "gregorian.h"

namespace lab2
{
Gregorian::Gregorian(){} // Base (Date_impl) computed everything by default

Gregorian::Gregorian(int year, int month, int day)
    :Date_impl(year, month, day)
{
    check_date(day, month, year);
    julian_day_ = julian_from_date(day, month, year);
}

Gregorian::Gregorian(const Date& src)
    :Date_impl(src)
{
    date_from_julian(julian_day_, day_, month_, year_);
}

Date& Gregorian::operator=(const Date& src)
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

Gregorian::~Gregorian(){}

bool Gregorian::is_leap_year(int year) const {return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));}

double Gregorian::julian_from_date(int day, int month, int year) const
{
    // ** From http://www.calendarhome.com/plugins/content/calendarhomecontent/converter/calendar.js
    return (GREGORIAN_EPOCH - 1) + (365 * (year - 1)) + floor((year - 1) / 4.0) +
               (-floor((year - 1) / 100.0)) + floor((year - 1) / 400.0) +
               floor((((367 * month) - 362) / 12.0) +
                          ((month <= 2) ? 0 : (is_leap_year(year) ? -1 : -2)) + day);
}

void Gregorian::date_from_julian(double julian, int &day, int &month, int &year) const
{
    // ** From http://www.calendarhome.com/plugins/content/calendarhomecontent/converter/calendar.js
    double wjd, depoch, quadricent, dqc, cent, dcent, quad, dquad, yindex, yearday, leapadj;
    double jd = julian;

    wjd = floor(jd - 0.5) + 0.5;
    depoch = wjd - GREGORIAN_EPOCH;
    quadricent = floor(depoch / 146097.0);
    dqc = mod(depoch, 146097.0);
    cent = floor(dqc / 36524.0);
    dcent = mod(dqc, 36524.0);
    quad = floor(dcent / 1461.0);
    dquad = mod(dcent, 1461.0);
    yindex = floor(dquad / 365.0);
    year = (quadricent * 400) + (cent * 100) + (quad * 4) + yindex;
    if (!((cent == 4) || (yindex == 4))) {
        year++;
    }
    yearday = wjd - julian_from_date(1, 1, year);
    leapadj = ((wjd < julian_from_date(1, 3, year)) ? 0 :
                                    (is_leap_year(year) ? 1 : 2));

    month = floor((((yearday + leapadj) * 12) + 373) / 367.0);
    day = (wjd - julian_from_date(1, month, year)) + 1;
}
} //namespace lab2
