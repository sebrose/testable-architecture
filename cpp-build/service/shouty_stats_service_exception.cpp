#include "shouty_stats_service_exception.hpp"

shouty_stats_service_exception::shouty_stats_service_exception(
    const std::string & message
)
    : std::runtime_error(message)
{
}
