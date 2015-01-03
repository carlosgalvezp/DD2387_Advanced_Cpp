#include <characters/wise_man.h>

using namespace lab3::characters;

Wise_Man::Wise_Man()
{}

Wise_Man::Wise_Man(const std::string &name)
    : Human(name, TYPE_WISE_MAN)
{}

Wise_Man::~Wise_Man()
{

}
