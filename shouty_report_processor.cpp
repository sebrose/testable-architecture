#include "shouty_report_processor.hpp"
#include "tinyxml2.hpp"
#include <iomanip>
#include <sstream>
#include <string>

using std::ostringstream;
using std::stod;
using std::setprecision;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

shouty_report_processor::shouty_report_processor(
    const std::vector<mileage_claim> & claims
)
    : claims_(claims)
    , stats_service_(new shouty_stats_service())
{
}

void shouty_report_processor::process() const
{
    XMLDocument xmldoc;
    xmldoc.InsertEndChild(xmldoc.NewDeclaration());
    
    XMLElement * root = xmldoc.NewElement("ecoReport");
    xmldoc.InsertEndChild(root);

    for (auto && claim : claims_)
    {
        XMLDocument response;
        response.Parse(stats_service_->get_revenue_for_customer(claim.customer_id()).c_str());
        double revenue = stod(response.FirstChildElement("CustomerStats")->Attribute("revenue"));

        ostringstream oss;
        oss << setprecision(7) << (revenue / claim.miles());

        XMLElement * child = xmldoc.NewElement("ecoStat");
        child->SetAttribute("RevenuePerMile", oss.str().c_str());
        child->SetAttribute("SalesPersonName", claim.name().c_str());
        root->InsertEndChild(child);
    }

    xmldoc.SaveFile("report.xml");
}
