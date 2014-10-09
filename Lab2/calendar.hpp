#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"
#include <map>
#include <utility>
#include <iomanip>
#include <sstream>

#define CAL_TEXT_WIDTH 28

namespace lab2
{

typedef std::multimap<Date*, std::string> mmap;

template <typename T>
class Calendar
{
public:
    enum format{list, cal, iCalendar};

    Calendar();
    ~Calendar();

    Calendar<T>& operator= (const Calendar<T>& src);

    bool set_date(int year, int month, int day);

    bool add_event(std::string event, int day, int month);
    bool add_event(std::string event, int day, int month, int year);
    bool add_event(std::string event, int day);
    bool add_event(std::string event);

    bool remove_event(std::string event, int day, int month, int year);
    bool remove_event(std::string event, int day, int month);
    bool remove_event(std::string event, int day);
    bool remove_event(std::string event);

    void set_format(format f);

    template<typename T1>
    friend std::ostream& operator<<(std::ostream& os, const Calendar<T1>& calendar);
private:
    struct cmp_date{
        bool operator()(const Date* d1, const Date* d2) const {
            return *d1 < *d2;
        }
    };

    std::ostream& print_list(std::ostream& os) const;
    std::ostream& print_cal (std::ostream& os) const;
    std::ostream& print_ical(std::ostream& os) const;

    Date* current_date_;
    std::multimap<Date*, std::string, cmp_date> events_;
    format format_;
};

// =============================================================================
// =============================================================================
// =============================================================================


template<typename T>
Calendar<T>::Calendar()
{
    (void)static_cast<Date*>((T*)0); // To check whether T is child of Date
    current_date_ = new T();         // Sets current time
}

template<typename T>
Calendar<T>::~Calendar()
{
    // Delete current date
    delete current_date_;

    // Delete events
    for (auto it = events_.begin(); it != events_.end(); ++it)
        delete it->first; // it = std::pair, in which the "first" element is the key
}

template<typename T>
bool Calendar<T>::set_date(int year, int month, int day)
{
    // ** Check date correcntess
    try
    {
        current_date_->check_date(day, month, year);
    }
    catch(std::out_of_range& e){return false;}

    // ** Set date
    delete current_date_;
    current_date_ = new T(day, month, year);
    return true;
}

template<typename T>
bool Calendar<T>::add_event(std::string event, int day, int month, int year)
{
    // ** Check date correctness
    try
    {
        current_date_->check_date(day, month, year);
    }
    catch(std::out_of_range& e){return false;}

    // ** Search to check if we already have this event
    T d(day, month, year);
    std::pair<mmap::const_iterator, mmap::const_iterator> range
            = events_.equal_range(&d);

    for(mmap::const_iterator it = range.first; it != range.second; ++it)
    {
        if(event == it->second) // Same string name
            return false;
    }
    // ** Not found -> insert
    events_.insert(std::pair<Date*, std::string>(new T(day, month, year), event));
    return true;
}

template<typename T>
bool Calendar<T>::add_event(std::string event, int day, int month)
{
    return add_event(event, day, month, current_date_->year());
}

template<typename T>
bool Calendar<T>::add_event(std::string event, int day)
{
    return add_event(event, day, current_date_->month(), current_date_->year());
}

template<typename T>
bool Calendar<T>::add_event(std::string event)
{
    return add_event(event, current_date_->day(), current_date_->month(), current_date_->year());
}

template<typename T>
bool Calendar<T>::remove_event(std::string event, int day, int month, int year)
{
    // ** Check date correctness
    try
    {
        current_date_->check_date(day, month, year);
    }
    catch(std::out_of_range& e){return false;}

    // ** Search to check if we already have this event
    T d(day, month, year);
    std::pair<mmap::const_iterator, mmap::const_iterator> range
            = events_.equal_range(&d);

    for(mmap::const_iterator it = range.first; it != range.second; ++it)
    {
        if(event == it->second) // Element found -> delete
        {
            delete it->first;
            events_.erase(it); //Delete it before we remove its pointer!!
            return true;
        }
    }
    return false;
}

template<typename T>
bool Calendar<T>::remove_event(std::string event, int day, int month)
{
   return remove_event(event, day, month, current_date_->year());
}

template<typename T>
bool Calendar<T>::remove_event(std::string event, int day)
{
   return remove_event(event, day, current_date_->month(), current_date_->year());
}

template<typename T>
bool Calendar<T>::remove_event(std::string event)
{
   return remove_event(event, current_date_->day(), current_date_->month(), current_date_->year());
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Calendar<T>& calendar)
{
    switch (calendar.format_)
    {
        case Calendar<T>::format::cal:
            return calendar.print_cal(os);
            break;

        case Calendar<T>::format::iCalendar:
            return calendar.print_ical(os);
            break;

        default:
            return calendar.print_list(os);
            break;
    }
}

template<typename T>
void Calendar<T>::set_format(format f)
{
    format_ = f;
}

template<typename T>
std::ostream& Calendar<T>::print_list(std::ostream& os) const
{
    for(auto it : events_)
    {
        if(*it.first > *current_date_)
            os << *it.first << " : " << it.second << std::endl;
    }
    return os;
}

template<typename T>
std::ostream& Calendar<T>::print_cal(std::ostream& os) const
{
    std::stringstream ss;
    ss << current_date_->month_name()<<" " << current_date_->year();
    std::string heading(ss.str());
    // Center the heading
    unsigned int pad_size = (CAL_TEXT_WIDTH - heading.size())/2;
    for(std::size_t i = 0 ; i < pad_size; ++i)
        os << " ";
    os << heading;
    for(std::size_t i = 0 ; i < pad_size; ++i)
        os << " ";
    os << std::endl;

    //Day names
    const std::vector<std::string>& day_names = current_date_->get_day_names();
    for(std::size_t i = 0; i < day_names.size(); ++i)
        os << " " << day_names.at(i).substr(0,2) << " ";
    os << std::endl;

    // Days
    T tmp(1, current_date_->month(), current_date_->year());
    Date* tmp_date = &tmp;
    std::size_t p0 = 4*(tmp_date->week_day() - 1);
    // Leading spaces before day 1
    for(std::size_t j = 0; j < p0; ++j)
        os << " ";
    for (std::size_t i = 1; i <= current_date_->days_this_month(); ++i)
    {
        T tmp2 = T(i, current_date_->month(), current_date_->year());
        // Print day
        if (i == current_date_->day())                      // Current day
            os << "<" << std::setw(2) << i << ">";

        else if(events_.find(&tmp2) != events_.end())       // Special day
            os << " " << std::setw(2) << i << "*";
        else                                               // Normal day
            os << " " << std::setw(2) << i << " ";
        p0 += 4;
        if (p0 == CAL_TEXT_WIDTH)
        {
            p0 = 0;
            os << std::endl;
        }
    }

    os << std::endl << std::endl;

    // Print a list of events this month
    for(auto it : events_)
    {
        if(it.first->month() == current_date_->month())
            os << "  " << *it.first << ": " << it.second << std::endl;
    }

    return os;
}

template<typename T>
std::ostream& Calendar<T>::print_ical(std::ostream& os) const
{
    // ** Follow RFC2445 standard
    // Heading
    os << "BEGIN:VCALENDAR\n";
    os << "VERSION:2.0\n";
    os << "PRODID:-//CPROG Calendar//Made by Carlos Galvez//\n";
    os << "CALSCALE:GREGORIAN\n";
    // Events
    for(auto it : events_)
    {
        Date* d = it.first;
        os << "BEGIN:VEVENT\n";
        os << "DTSTART:"<< d->year() << std::setfill('0') << std::setw(2) << d->month()
                                     << std::setfill('0') << std::setw(2) << d->day()
           << "T080000\n";
        os << "DTEND:"<< d->year() << std::setfill('0') << std::setw(2) << d->month()
                                     << std::setfill('0') << std::setw(2) << d->day()
           << "T090000\n";
        os << "SUMMARY:"<< it.second << "\n";
        os << "END:VEVENT\n";
    }
    // Finish
    os << "END:VCALENDAR\n";
    return os;
}

} // namespace lab2



#endif // CALENDAR_H
