#ifndef ECO_STAT_COLLECTION_BUILDER_INCLUDED
#define ECO_STAT_COLLECTION_BUILDER_INCLUDED

#include "eco_stat.hpp"
#include <string>
#include <map>
#include <vector>

namespace shouty_report
{

class eco_stat_collection_builder
{
public:
    std::vector<eco_stat> build() const;

    eco_stat_collection_builder & with_sales_person_rpm(
      const std::string & name,
      double rpm
    );

private:
    static const std::vector<eco_stat> default_eco_stat_collection;

    std::map<std::string, double> eco_stat_data;
};

}

#endif
