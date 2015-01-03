#include <characters/wise_man.h>

using namespace lab3::characters;

Wise_Man::Wise_Man()
{}

Wise_Man::Wise_Man(const std::string &name, Place *place)
    : Human(name, TYPE_WISE_MAN, place)
{}

Wise_Man::~Wise_Man()
{

}
