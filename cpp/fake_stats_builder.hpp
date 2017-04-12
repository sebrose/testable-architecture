#ifndef FAKE_STATS_BUILDER_INCLUDED
#define FAKE_STATS_BUILDER_INCLUDED

#include <string>

class fake_stats_builder
{
public:
    std::string build() const;
    
    fake_stats_builder & with_customer_id(int value);
    fake_stats_builder & with_revenue(double value);
    
private:
    std::string fake_data;    
};

#endif
