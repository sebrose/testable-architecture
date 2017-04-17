#include "production_stats_service.hpp"
#include "shouty_stats_service.hpp"
//#include <tinyxml2.hpp>

//using std::stod;
//using std::string;
//using tinyxml2::XMLDocument;

production_stats_service::production_stats_service()
    : stats_service(new shouty_stats_service())
{
}

double production_stats_service::get_revenue(int /*customer_id*/) const
{
    throw "unimplemented";

    // Hint: you can copy code from shouty_report_processor.cpp to
    // implement this method, including the behaviour to extract the
    // revenue value as a double from the XML
}
