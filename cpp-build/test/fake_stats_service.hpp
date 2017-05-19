#ifndef FAKE_STATS_SERVICE_INCLUDED
#define FAKE_STATS_SERVICE_INCLUDED

#include "stats_service.hpp"
#include <map>
#include <string>

using shouty_report::stats_service;

class fake_stats_service : public stats_service
{
public:
    explicit fake_stats_service(const std::string & initialisation_data);
    virtual double get_revenue(int customer_id) const;

private:
    std::map<int, double> revenue_data;
};

#endif
