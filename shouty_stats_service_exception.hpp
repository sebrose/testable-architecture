#ifndef SHOUTY_STATS_SERVICE_EXCEPTION_INCLUDED
#define SHOUTY_STATS_SERVICE_EXCEPTION_INCLUDED

#include <stdexcept>
#include <string>

class shouty_stats_service_exception : public std::runtime_error
{
public:
    explicit shouty_stats_service_exception(const std::string &);
};

#endif
