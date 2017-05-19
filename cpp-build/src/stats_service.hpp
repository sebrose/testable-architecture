#ifndef STATS_SERVICE_INCLUDED
#define STATS_SERVICE_INCLUDED

namespace shouty_report
{

class stats_service
{
public:
    virtual ~stats_service() {}
    virtual double get_revenue(int customer_id) const = 0;
};

}

#endif
