#include "eco_stat_collection_builder.hpp"

namespace shouty_report
{
  const std::vector<eco_stat> eco_stat_collection_builder::default_eco_stat_collection= {
     eco_stat("David Allen", 1.234f),
     eco_stat("Lisa Crispin", 0.025f),
     eco_stat("Ian Dees", 98.76f)
 };

  std::vector<eco_stat> eco_stat_collection_builder::build() const
  {
      if (eco_stat_data.size() == 0)
      {
          return default_eco_stat_collection;
      }
      else
      {
          std::vector<eco_stat> eco_stat_collection;

          for (auto & entry : eco_stat_data)
          {
              eco_stat_collection.push_back(
                  eco_stat(entry.first, entry.second)
              );
          }

          return eco_stat_collection;
      }
  }

  eco_stat_collection_builder &
  eco_stat_collection_builder::with_sales_person_rpm(
      const std::string & name,
      double rpm
  )
  {
      eco_stat_data[name] = rpm;

      return *this;
  }

}
