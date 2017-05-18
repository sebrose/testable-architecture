#include "fake_stats_service_builder.hpp"

#include <sstream>

namespace shouty_report
{
    stats_service fake_stats_service_builder::build() const
    {
        if (builder_data.size() == 0)
        {
            return fake_stats_service(default_customer_data);
        }
        else
        {
            std::ostringstream data;
            std::string separator = "";

            for (auto & entry : builder_data)
            {
                data << separator << entry.first << "," << entry.second;
                separator = ";";
            }

            return fake_stats_service(data.str());
        }
    }

    fake_stats_service_builder &
    fake_stats_service_builder::with_customer_revenue(
        int id,
        const std::string&  revenue
    )
    {
        builder_data[id] = revenue;

        return *this;
    }
}
