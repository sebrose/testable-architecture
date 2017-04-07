#include "shouty_report_processor.hpp"

#include <sstream>
#include <iomanip>

#include "tinyxml2.hpp"
using namespace tinyxml2;

shouty_report_processor::shouty_report_processor(
    const std::vector<mileage_claim> & claims)
    : claims_(claims)
    , stats_service_(new shouty_stats_service())
{
}

void shouty_report_processor::process() const
{
    XMLDocument xmldoc;
    xmldoc.InsertEndChild(xmldoc.NewDeclaration());

    XMLElement* root = xmldoc.NewElement("ecoReport");
    xmldoc.InsertEndChild(root);

    for (auto && claim : claims_)
    {
        XMLDocument response;
        response.Parse(stats_service_->get_revenue_for_customer(claim.customer_id()).c_str());
        double revenue =  atof(response.FirstChildElement("CustomerStats")->Attribute("revenue"));

        std::ostringstream revenue_per_mile_output;
        revenue_per_mile_output << std::setprecision(7) << revenue/claim.miles();

        XMLElement* child = xmldoc.NewElement("ecoStat");
        child->SetAttribute("RevenuePerMile", revenue_per_mile_output.str().c_str());
        child->SetAttribute("SalesPersonName", claim.name().c_str());
        root->InsertEndChild(child);
    }

    xmldoc.SaveFile("report.xml");
}
