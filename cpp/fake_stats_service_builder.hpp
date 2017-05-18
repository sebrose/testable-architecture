#ifndef FAKE_STATS_SERVICE_BUILDER_INCLUDED
#define FAKE_STATS_SERVICE_BUILDER_INCLUDED

#include "fake_stats_service.hpp"
#include <string>

namespace shouty_report
{

class fake_stats_service_builder
{
public:
    stats_service build() const;

    fake_stats_service_builder & with_customer_revenue(
        int id,
        const std::string&  revenue
    );

private:
    std::string default_customer_data = "19,123456.78;22,123456.78;57,123456.78";
    std::map<int, std::string> builder_data;
};

}

#endif
