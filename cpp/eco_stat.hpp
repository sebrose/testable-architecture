#ifndef ECO_STAT_INCLUDED
#define ECO_STAT_INCLUDED

#include <ostream>
#include <string>

struct eco_stat
{
    eco_stat(const std::string & sales_person_name_,
             double revenue_per_mile_);

    std::string sales_person_name;
    double revenue_per_mile;
}; 

bool operator==(const eco_stat & lhs, const eco_stat & rhs);

std::ostream & operator<<(std::ostream & os, const eco_stat & es);

#endif