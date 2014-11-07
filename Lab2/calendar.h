#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"
#include <set>
#include <utility>
#include <iomanip>
#include <sstream>

#define CAL_TEXT_WIDTH 28

namespace lab2
{

/**
 * @brief Class representing an event, comprised of a date and the actual event (string)
 */
template <typename T>
struct Event
{
    Date* date_;
    std::string event_;

    Event(){}
    explicit Event(Date* date, std::string event)
        :date_(date), event_(event){}

    Event(const Event<T>& src)                   // "True" Copy constructor
        :event_(src.event_)
    {
        date_ = new T(*src.date_);
    }

    Event<T>& operator=(const Event<T>& src)     // "True" assignment operator
    {
        if(&src != this)
        {
            delete date_;
            date_ = new T(src.date_);
            event_= src.event_;
        }
        return *this;
    }

    template <typename S>
    Event(const Event<S>& src)                  // Constructor with other-type event
        :event_(src.event_)
    {
        date_ = new T(*src.date_);
    }

    template <typename S>
    Event<T>& operator=(const Event<S>& src)   // Copy-assignment with other-type event
    {
        if (&src != this)
        {
            delete date_;
            date_ = new T(src.date_);
            event_= src.event_;
        }
        return *this;
    }

    ~Event(){delete date_;}                     // Destructor

    bool operator<(const Event& src)    const   {return *this->date_ < *src.date_;}
    bool operator == (const Event& src) const
    {
        return *this->date_  == *src->date_ &&
                this->event_ == src->event;
    }

    bool operator!=(const Event& src)   const   {return !(*this == src);}
};

template <typename T>
class Calendar
{
public:
    enum format{list, cal, iCalendar};

    typedef typename std::multiset<Event<T>>::const_iterator mset_const_iterator;
    typedef typename std::multiset<Event<T>>::iterator mset_iterator;

    Calendar();
    Calendar(const Calendar &src);              // Copy constructor
    Calendar& operator= (const Calendar &src);  // Copy-assignment operator

    template<typename S>
    Calendar(const Calendar<S>& src); // Copy constructor (different type)

    template<typename S>
    Calendar& operator= (const Calendar<S>& src); // Copy-assignment operator

    ~Calendar();

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

    template<typename S>
    friend std::ostream& operator<<(std::ostream& os, const Calendar<S>& calendar);

private:    
    template<typename>
    friend class Calendar; // So that copy-constructor and assigment operator can operate on Calendar with different types

    std::ostream& print_list(std::ostream& os) const;
    std::ostream& print_cal (std::ostream& os) const;
    std::ostream& print_ical(std::ostream& os) const;
    bool contains_date(const Date& date) const;

    Date* current_date_;
    std::multiset<Event<T>> events_;
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
    format_ = format::list;
}

template<typename T>
Calendar<T>::Calendar(const Calendar<T> &src)
{
    (void)static_cast<Date*>((T*)0); // To check whether T is child of Date

    current_date_ = new T(*src.current_date_);
    // Copy events
    events_.clear();
    typename std::multiset<Event<T>>::iterator it;
    for(it = src.events_.begin(); it != src.events_.end(); ++it)
    {
        events_.insert(*it); // Multiset creates a copy
    }
    format_ = src.format_;
}

template<typename T>
Calendar<T>& Calendar<T>::operator =(const Calendar<T>& src)
{
    (void)static_cast<Date*>((T*)0); // To check whether T is child of Date

    if(&src != this)
    {
        delete current_date_;
        current_date_ = new T(*src.current_date_);
        // Copy events
        events_.clear();
        for(auto it = src.events_.begin(); it != src.events_.end(); ++it)
        {
            events_.insert(*it); // Multiset creates a copy
        }
        format_ = src.format_;
    }
    return *this;
}

template<typename T>
template<typename S>
Calendar<T>::Calendar(const Calendar<S>& src)
{
    (void)static_cast<Date*>((T*)0); // To check whether T is child of Date
    (void)static_cast<Date*>((S*)0); // To check whether S is child of Date

    current_date_ = new T(*src.current_date_);
    // Copy events
    events_.clear();
    for(auto it = src.events_.begin(); it != src.events_.end(); ++it)
    {
        events_.insert(static_cast<Event<T>>(*it));
    }
    format_ = static_cast<Calendar<T>::format>(src.format_);
}

template<typename T>
template<typename S>
Calendar<T>& Calendar<T>::operator=(const Calendar<S>& src)
{
    (void)static_cast<Date*>((T*)0); // To check whether T is child of Date
    (void)static_cast<Date*>((S*)0); // To check whether S is child of Date

    delete current_date_;
    current_date_ = new T(*src.current_date_);
    // Copy events
    events_.clear();
    for(auto it = src.events_.begin(); it != src.events_.end(); ++it)
    {
        events_.insert(static_cast<Event<T>>(*it));
    }
    format_ = static_cast<Calendar<T>::format>(src.format_);
    return *this;
}

template<typename T>
Calendar<T>::~Calendar()
{
    // Delete current date
    delete current_date_;

    // Delete events
    for (mset_iterator it = events_.begin(); it != events_.end(); ++it)
    {
        events_.erase(it);
    }
}

template<typename T>
bool Calendar<T>::set_date(int year, int month, int day)
{
    // ** Check date correctness
    try
    {
        current_date_->check_date(day, month, year);
    }
    catch(std::out_of_range& e){return false;}

    // ** Set date
    delete current_date_;
    current_date_ = new T(year, month, day);
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
    Event<T> e(new T(year, month, day), event);
    std::pair<mset_iterator, mset_iterator> range = events_.equal_range(e);

    for(mset_iterator it = range.first; it != range.second; ++it) // Can have multiple events in same date
    {
        if(event == it->event_) // Same string name
            return false;
    }
    // ** Not found -> insert        
    events_.insert(e);
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
    Event<T> e(new T(year, month, day), event);
    std::pair<mset_iterator, mset_iterator> range = events_.equal_range(e);

    for(mset_iterator it = range.first; it != range.second; ++it) // Can have multiple events in same date
    {
        if(event == it->event_) // Element found -> remove
        {
            events_.erase(it);
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
void Calendar<T>::set_format(Calendar<T>::format f)
{
    format_ = f;
}

template<typename T>
std::ostream& Calendar<T>::print_list(std::ostream& os) const
{
    for(mset_iterator it = events_.begin(); it != events_.end(); ++it)
    {
        if(*(it->date_) > *current_date_)
            os << *(it->date_) << " : " << it->event_ << std::endl;
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
    T tmp(current_date_->year(), current_date_->month(), 1);
    Date& tmp_date = tmp;
    std::size_t p0 = 4*(tmp_date.week_day() - 1);
    // Leading spaces before day 1
    for(std::size_t j = 0; j < p0; ++j)
    {
        os << " ";
    }

    for (std::size_t i = 1; i <= current_date_->days_this_month(); ++i)
    {
        T tmp2 = T(current_date_->year(), current_date_->month(), i);
        // Print day
        if (i == current_date_->day())                      // Current day
            os << "<" << std::setw(2) << i << ">";

        else if(contains_date(tmp2))       // Special day
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
        if(it.date_->month() == current_date_->month())
            os << "  " << *it.date_ << ": " << it.event_<< std::endl;
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
        Date* d = it.date_;
        os << "BEGIN:VEVENT\n";
        os << "DTSTART:"<< d->year() << std::setfill('0') << std::setw(2) << d->month()
                                     << std::setfill('0') << std::setw(2) << d->day()
           << "T080000\n";
        os << "DTEND:"<< d->year() << std::setfill('0') << std::setw(2) << d->month()
                                     << std::setfill('0') << std::setw(2) << d->day()
           << "T090000\n";
        os << "SUMMARY:"<< it.event_ << "\n";
        os << "END:VEVENT\n";
    }
    // Finish
    os << "END:VCALENDAR\n";
    return os;
}

template<typename T>
bool Calendar<T>::contains_date(const Date& date) const
{
    for(mset_const_iterator it = events_.begin(); it != events_.end(); ++it)
    {
        if(*it->date_ == date)
            return true;
    }
    return false;
}

} //lab2 namespace




#endif // CALENDAR_H
