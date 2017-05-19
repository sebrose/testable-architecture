#include "mileage_claim.hpp"
#include "tinyxml2.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using std::string;
using tinyxml2::XMLDocument;
using namespace shouty_report;

namespace {

void mileage_claim_can_be_created_from_strings()
{
    const mileage_claim claim("David Allen", 37000, 99);
    assert(claim.name() == "David Allen");
    assert(claim.miles() == 37000);
    assert(claim.customer_id() == 99);
}

void extract_data_from_xml()
{
    const char * xml = "<CustomerStats id=\"22\" revenue=\"300.00\"/>";
    XMLDocument doc;
    doc.Parse(xml);
    const string revenue(doc.FirstChildElement("CustomerStats")->Attribute("revenue"));
    assert(revenue == "300.00");
}

} // namespace

int main()
{
    mileage_claim_can_be_created_from_strings();
    extract_data_from_xml();

    std::cout << "tests (unit) passed" << std::endl;
}
