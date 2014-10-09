#include "date.h"

namespace lab2
{

Date::Date(){}
Date::~Date(){}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    os << d.year() << "-" << std::setfill('0') << std::setw(2) << d.month() << "-"
                          << std::setfill('0') << std::setw(2) << d.day();
    return os;
}

// =============================================================================
// =============================================================================
// =============================================================================

Date_impl::Date_impl()
    : days_week_(N_DAYS_WEEK_DEFAULT),
      months_year_(N_MONTHS_YEAR_DEFAULT)
{
    day_names_ = day_names_default;
    month_names_ = month_names_default;

    currentDate(day_, month_, year_);
    julian_day_ = julian_day_default(day_, month_, year_);
}

Date_impl::~Date_impl(){}

Date_impl::Date_impl(int day, int month, int year):
    day_(day), month_(month), year_(year),
    days_week_(N_DAYS_WEEK_DEFAULT),
    months_year_(N_MONTHS_YEAR_DEFAULT)
{
    check_date(day, month, year);

    day_names_ = day_names_default;
    month_names_ = month_names_default;

    julian_day_ = julian_day_default(day_, month_, year_);
}

Date_impl::Date_impl(int day, int month, int year,
                     const std::vector<std::string> &day_names,
                     const std::vector<std::string> &month_names):
    day_(day), month_(month), year_(year),
    days_week_(day_names.size()),
    months_year_(month_names.size())
{
    check_date(day, month, year);

    day_names_ = day_names;
    month_names_ = month_names;
    julian_day_ = julian_day_default(day_, month_, year_);
}

int Date_impl::year()  const{ return year_;}
int Date_impl::month() const{ return month_;}
int Date_impl::day()   const{ return day_;}

int Date_impl::week_day()         const{ return ((int)(julian_day_ + 1.5)) % days_per_week();}
int Date_impl::days_this_month()  const{ return days_in_month(month_, year_);}

int Date_impl::days_in_month(int month, int year) const
{
    if(month == 2) // February
    {
        if (is_leap_year(year))
            return 29;
        else
            return 28;
    }
    else
    {
        if( (month < 7 && month % 2 != 0) || (month >=7 && month % 2 == 0))
            return 31;
        else
            return 30;
    }
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
    int next_month = ((month_-1 + n)% (months_year_)) + 1;
    int n_years = floor(n/months_year_);
    int next_year = year_ + n_years + (int)(n > 0? next_month < month_ : next_month > month_);

    if(day_ > days_in_month(next_month, next_year)) // Can't do it => just add n x 30 days
    {
        julian_day_ += n*30;
        date_from_julian(julian_day_, day_, month_, year_);
    }
    else // Don't change the day
    {
        month_ = next_month;
        year_ = next_year;
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

    return *this;
}

int Date_impl::mod_julian_day()              const {return julian_day_ - MOD_JULIAN_DATE_DIFF; }

void Date_impl::check_date(int day, int month, int year) const
{
    // ** Check for negatives
    if (day <= 0 || month <=0 || year <=0)  throw std::out_of_range("Invalid date!");

    // ** Check days and months
    if (month > months_year_)               throw std::out_of_range("Invalid date!");
    if (day > days_in_month(month, year))   throw std::out_of_range("Invalid date!");
}

const std::vector<std::string>& Date_impl::get_day_names() const{return day_names_;}

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

} // namespace lab2




