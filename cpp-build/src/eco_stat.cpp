#include "eco_stat.hpp"
#include <ostream>

namespace shouty_report
{
  eco_stat::eco_stat(const std::string & sales_person_name_,
           double revenue_per_mile_)
     : sales_person_name(sales_person_name_)
     , revenue_per_mile(revenue_per_mile_)
  {

  }

  bool operator==(const eco_stat & lhs, const eco_stat & rhs)
  {
      return ((lhs.sales_person_name == rhs.sales_person_name)
              && (lhs.revenue_per_mile == rhs.revenue_per_mile));
  }

  bool operator!=(const eco_stat & lhs, const eco_stat & rhs)
  {
      return !(lhs == rhs);
  }

  std::ostream & operator<<(std::ostream & os, const eco_stat & es)
  {
      os << "eco_stat[sales_person_name = \""
         << es.sales_person_name
         << "\", revenue_per_mile = \""
         << es.revenue_per_mile
         << "\"]"
         << std::endl;
      return os;
  }
}
