#include "production_stats_service.hpp"
#include "shouty_stats_service.hpp"

#include <tinyxml2.hpp>
#include <memory>
#include <sstream>

using std::ostringstream;
using std::stod;
using tinyxml2::XMLDocument;

namespace shouty_report
{

production_stats_service::production_stats_service()
    : stats_service(std::make_unique<shouty_stats_service>())
{
}

double production_stats_service::get_revenue(int /* customer_id */) const
{
    /*
        ostringstream xmlRequest;
        xmlRequest << "<Customer id=\"" << customer_id << "\"/>";
        XMLDocument response;
        response.Parse(stats_service->get_revenue_for_customer(xmlRequest.str()).c_str());
        return stod(response.FirstChildElement("CustomerStats")->Attribute("revenue"));
    */

    throw "unimplemented - uncomment code above and delete this exception";
}

}
