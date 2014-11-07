#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>
#include <iostream>
#include "kattistime.h"
#include <ctime>
#include <cmath>
#include <iomanip>
#include <stdexcept>

#define KATTIS

#define MOD_JULIAN_DATE_DIFF 2400000.5
#define GREGORIAN_EPOCH 1721425.5
namespace lab2
{

/**
 * @brief Abstract class that serves only as an interface. No data is contained
 * here, just the functions declaration.
 */
class Date
{
public:
    virtual ~Date();
    virtual Date& operator=(const Date& src)  = 0; //This is required. Otherwise an implicit operator= is used!

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

    virtual int mod_julian_day()                          const = 0;
    virtual void check_date(int day, int month, int year) const = 0;

    // For extra exercise
    virtual const std::vector<std::string>& get_day_names()     const = 0;
protected:

private:

};
/**
 * @brief Prints a date
 * @param os ostream
 * @param d date
 * @return
 */
std::ostream& operator<<(std::ostream& os, const Date& d);

/**
 * @brief Modulus function (also valid for negative numbers, as opposed to %)
 * @param a
 * @param b
 * @return
 */
int mod(int a, int b);
/**
 * @brief sign function
 * @param x
 * @return 1 if x>=0, -1 if x < 0
 */
int sign(double x);

// =============================================================================
// =============================================================================
// =============================================================================

/**
 * @brief Implementation of the common functionalities of a Date class
 */
class Date_impl : public Date
{
public:
    Date_impl();
    Date_impl(int year, int month, int day);
    Date_impl(const Date& src);
    virtual Date& operator=(const Date& src) = 0;
    ~Date_impl(); // Already virtual since base destructor is virtual

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

    // For extra exercise
    const std::vector<std::string>& get_day_names() const;
protected:
    int day_, month_, year_;
    double julian_day_;
    int days_week_, months_year_;

    virtual double  julian_from_date(int day, int month, int year)                  const = 0;
    virtual void    date_from_julian(double julian, int& day, int&month, int& year) const = 0;
    virtual bool    is_leap_year(int year)                                          const = 0;

    int days_in_month(int month, int year) const;

private:

    /**
     * @brief Retrieves current date (GMT). This is given only Gregorian format, so
     * we need to convert to Julian afterwards if needed.
     * @param day
     * @param month
     * @param year
     */
    void currentDate(int& day, int& month, int&year);

    /**
     * @brief Computes the julian day assuming a Gregorian date input
     * @param day
     * @param month
     * @param year
     * @return
     */
    double julian_day_default(int day, int month, int year);
};

// Common to Gregorian and Julian
static std::vector<int> month_n_days_{31,28,31,30,31,30,31,31,30,31,30,31};

static std::vector<std::string> day_names_ ={"monday", "tuesday", "wednesday", "thursday",
 "friday", "saturday", "sunday"};
static std::vector<std::string> month_names_ = {"january", "february", "march", "april", "may", "june",
    "july", "august", "september", "october", "november", "december"};

} // namespace lab2
#endif // DATE_H
