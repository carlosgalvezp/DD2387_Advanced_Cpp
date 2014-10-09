#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>
#include <iostream>
#include "kattis_time.h"
#include <ctime>
#include <cmath>
#include <iomanip>
#include <stdexcept>

//#define KATTIS

#define N_DAYS_WEEK_DEFAULT    7
#define N_MONTHS_YEAR_DEFAULT 12

#define MOD_JULIAN_DATE_DIFF 2400000.5
#define GREGORIAN_EPOCH 1721425.5
namespace lab2
{

/**
 * @brief Abstract class that serves only as an interface
 */
class Date
{
public:
    Date();
    virtual ~Date();

//    Date& operator=(const Date& src); ?
//    Date(const Date& src);

    virtual int year()                  const = 0;
    virtual int month()                 const = 0;
    virtual int day()                   const = 0;
    virtual int week_day()              const = 0;
    virtual int days_per_week()         const = 0;
    virtual int days_this_month()       const = 0;
    virtual int months_per_year()       const = 0;

    virtual std::string week_day_name() const = 0;
    virtual std::string month_name()    const = 0;

    virtual Date& operator++() = 0;
    virtual Date& operator--() = 0;

    virtual Date& operator+=(int n) = 0;
    virtual Date& operator-=(int n) = 0;

    virtual Date& add_month(int n = 1) = 0;
    virtual Date& add_year (int n = 1) = 0;

    virtual int operator-(const Date& src)      const = 0;

    virtual bool operator==(const Date& src)    const = 0;
    virtual bool operator!=(const Date& src)    const = 0;
    virtual bool operator< (const Date& src)    const = 0;
    virtual bool operator<=(const Date& src)    const = 0;
    virtual bool operator> (const Date& src)    const = 0;
    virtual bool operator>=(const Date& src)    const = 0;


    virtual int mod_julian_day() const = 0;
    virtual void check_date(int day, int month, int year) const = 0;

    virtual const std::vector<std::string>& get_day_names() const = 0;
protected:

private:

};
std::ostream& operator<<(std::ostream& os, const Date& d);

/**
 * @brief Implementation of the common functionalities of a Date class
 */
class Date_impl : public Date
{
public:
    Date_impl();
    Date_impl(int day, int month, int year);
    Date_impl(int day, int month, int year,
              const std::vector<std::string>& day_names,
              const std::vector<std::string>& month_names);

//    Date_impl& operator=(const Date& src);
//    Date_impl(const Date& src);
    virtual ~Date_impl();

    int year()                          const;
    int month()                         const;
    int day()                           const;
    int week_day()                      const;
    int days_per_week()                 const;
    int days_this_month()               const;
    int months_per_year()               const;

    std::string week_day_name()         const;
    std::string month_name()            const;

    Date& operator++();
    Date& operator--();

    Date& operator+=(int n);
    Date& operator-=(int n);

    int operator-(const Date& src)      const;

    Date& add_month(int n = 1);
    Date& add_year(int n = 1);

    bool operator==(const Date& src)    const;
    bool operator!=(const Date& src)    const;
    bool operator<(const Date& src)     const;
    bool operator<=(const Date& src)    const;
    bool operator>(const Date& src)     const;
    bool operator>=(const Date& src)    const;

    int mod_julian_day()                const;

    void check_date(int day, int month, int year) const;

    const std::vector<std::string>& get_day_names() const;
protected:
    int day_, month_, year_;
    std::vector<std::string> day_names_, month_names_;
    double julian_day_;
    const int days_week_, months_year_;
    const std::vector<std::string> day_names_default
    {"monday", "tuesday", "wednesday", "thursday",
     "friday", "saturday", "sunday"};
    const std::vector<std::string> month_names_default
    {"january", "february", "march", "april", "may", "june",
        "july", "august", "septembre", "october", "november", "december"};

    virtual double  julian_from_date(int day, int month, int year)                  const = 0;
    virtual void    date_from_julian(double julian, int& day, int&month, int& year) const = 0;
    virtual bool    is_leap_year(int year)                                          const = 0;

    int days_in_month(int month, int year) const;

private:
    void currentDate(int& day, int& month, int&year);
    double julian_day_default(int day, int month, int year);
};

} // namespace lab2
#endif // DATE_H
