#ifndef PRODUCTION_STATS_SERVICE_INCLUDED
#define PRODUCTION_STATS_SERVICE_INCLUDED

#include "shouty_stats_service.hpp"
#include "stats_service.hpp"
#include <memory>

namespace shouty_report
{

class production_stats_service : public stats_service
{
public:
    production_stats_service();
    virtual double get_revenue(int customer_id) const;
private:
    std::unique_ptr<shouty_stats_service> stats_service;
};

}

#endif
