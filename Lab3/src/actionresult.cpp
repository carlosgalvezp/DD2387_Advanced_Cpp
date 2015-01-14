#include "actionresult.h"

ActionResult::ActionResult(bool success)
    : success_(success), event_(EVENT_NULL)
{}

ActionResult::ActionResult(bool success, const std::string &event)
    : success_(success), event_(event)
{}
ActionResult::~ActionResult()
{}

