#ifndef ACTIONRESULT_H
#define ACTIONRESULT_H

#include <string>
#include <names.h>
struct ActionResult
{
    ActionResult(bool success_); // Not explicit on purpose, for compatibility reasons
    ActionResult(bool success_, const std::string &event);

    ~ActionResult();

    bool success_;
    std::string event_;

};

#endif // ACTIONRESULT_H
