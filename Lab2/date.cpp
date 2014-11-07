#include "date.h"

namespace lab2
{
Date::~Date(){}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    os << d.year() << "-" << std::setfill('0') << std::setw(2) << d.month() << "-"
                          << std::setfill('0') << std::setw(2) << d.day();
    return os;
}

int mod(int a, int b)
{
    return (a%b+b)%b;
}

int sign(double x)
{
    if (x >= 0)
        return 1;
    else
        return -1;
}

// =============================================================================
// =============================================================================
// =============================================================================

Date_impl::Date_impl()
{
    days_week_ = day_names_.size();
    months_year_ = month_names_.size();
    // Get current date (GMT). This is Gregorian, so we will convert later to Julian if needed
    currentDate(day_, month_, year_);
    julian_day_ = julian_day_default(day_, month_, year_);
}

Date_impl::Date_impl(const Date &src)
{
    days_week_ = day_names_.size();
    months_year_ = month_names_.size();
    julian_day_ = src.mod_julian_day() + MOD_JULIAN_DATE_DIFF;
}

Date_impl::Date_impl(int year, int month, int day):
    day_(day), month_(month), year_(year)
{
    days_week_ = day_names_.size();
    months_year_ = month_names_.size();
}

Date_impl::~Date_impl(){}

int Date_impl::year()  const{ return year_;}
int Date_impl::month() const{ return month_;}
int Date_impl::day()   const{ return day_;}

int Date_impl::week_day()         const{ return ((int)(julian_day_ + 0.5) % days_per_week()) + 1;}
int Date_impl::days_this_month()  const{ return days_in_month(month_, year_);}

int Date_impl::days_in_month(int month, int year) const
{
    if(month == 2 && is_leap_year(year)) // February
        return 29;
    else
        return month_n_days_[month-1];
}

int Date_impl::days_per_week()    const{ return days_week_;}
int Date_impl::months_per_year()  const{ return months_year_;}

std::string Date_impl::week_day_name()  const{return day_names_[week_day()-1];}
std::string Date_impl::month_name()     const{return month_names_[month()-1];}

Date& Date_impl::operator++()       { return operator+=(1); }
Date& Date_impl::operator--()       { return operator+=(-1);}
Date& Date_impl::operator-=(int n)  { return operator+=(-n);}
Date& Date_impl::operator+=(int n)
{
    julian_day_ += n;
    date_from_julian(julian_day_, day_, month_, year_);
    return *this;
}

bool Date_impl::operator ==(const Date& src) const {return mod_julian_day() == src.mod_julian_day();}
bool Date_impl::operator!=(const Date& src)  const {return mod_julian_day() != src.mod_julian_day();}
bool Date_impl::operator<(const Date& src)   const {return mod_julian_day() <  src.mod_julian_day();}
bool Date_impl::operator<=(const Date& src)  const {return mod_julian_day() <= src.mod_julian_day();}
bool Date_impl::operator>(const Date& src)   const {return mod_julian_day() >  src.mod_julian_day();}
bool Date_impl::operator>=(const Date& src)  const {return mod_julian_day() >= src.mod_julian_day();}

int Date_impl::operator -(const Date &src)   const {return mod_julian_day() - src.mod_julian_day();}

Date& Date_impl::add_month(int n)
{
    for(int i = 0; i < abs(n); ++i) // Add/subtract 1 month n times
    {
        int next_month, next_year;
        if(month() == 1 && sign(n) == -1) // One year less
        {
            next_month = months_per_year();
            next_year = year() - 1;
        }
        else if (month() == months_per_year() && sign(n) == 1) // one year more
        {
            next_month = 1;
            next_year = year() + 1;
        }
        else // just add/subtract 1 month
        {
            next_month = month() + sign(n);
            next_year = year();
        }

        if(day_ > days_in_month(next_month, next_year)) // Can't do it => just add/subtract 30 days
        {
            julian_day_ += 30*sign(n);
            date_from_julian(julian_day_, day_, month_, year_);
        }
        else // Don't change the day
        {
            month_ = next_month;
            year_ = next_year;
            julian_day_ = julian_from_date(day_, month_, year_);
        }
    }
    return *this;
}

Date& Date_impl::add_year(int n)
{
    int next_year = year_ + n;
    int max_day = days_in_month(month_, next_year);

    if(day_ > max_day) // The case of february and leap year
        day_ = max_day;
    year_ = next_year;

    julian_day_ = julian_from_date(day_, month_, year_);
    return *this;
}

int Date_impl::mod_julian_day()              const {return julian_day_ - MOD_JULIAN_DATE_DIFF; }

void Date_impl::check_date(int day, int month, int year) const
{
    // ** Check for negatives
    if (day <= 0 || month <=0 || year <=0) {throw std::out_of_range("Invalid date!");}

    // ** Check days and months
    if (month > months_year_)               {throw std::out_of_range("Invalid date!");}
    if (day > days_in_month(month, year))   {throw std::out_of_range("Invalid date!");}
}

void Date_impl::currentDate(int &day, int &month, int &year)
{
    time_t mytime;

#ifdef KATTIS
    k_time(&mytime);
#else
    time(&mytime);
#endif
    struct tm *t = gmtime(&mytime);
    year = t->tm_year + 1900;
    month = t->tm_mon + 1;
    day   = t->tm_mday;
}

double Date_impl::julian_day_default(int day, int month, int year)
{
    // From http://en.wikipedia.org/wiki/Julian_day
    int a = floor( (14 - month)/12.0 );
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;

    double julian = day + floor((153 * m + 2)/5.0) + 365*y + floor(y/4.0)
            - floor(y/100.0) + floor(y/400.0) - 32045.5;
    return julian;
}

// For extra exercise
const std::vector<std::string>& Date_impl::get_day_names() const {return day_names_;}

} // namespace lab2




