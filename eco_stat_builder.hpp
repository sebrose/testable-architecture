#ifndef ECO_STAT_BUILDER_INCLUDED
#define ECO_STAT_BUILDER_INCLUDED

#include "eco_stat.hpp"
#include <string>

class eco_stat_builder
{
public:
    eco_stat build() const;
    
    eco_stat_builder & with_sales_person(const std::string & value);
    eco_stat_builder & with_revenue_per_mile(double value);
    
private:
    std::string sales_person;
    double revenue_per_mile;
};

#endif

