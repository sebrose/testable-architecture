// DO NOT LOOK IN THIS FILE
// DO NOT LOOK IN THIS FILE
// DO NOT LOOK IN THIS FILE
// DO NOT LOOK IN THIS FILE

































#include "shouty_stats_service.hpp"
#include "shouty_stats_service_exception.hpp"
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <tinyxml2.hpp>

using std::getenv;
using std::map;
using std::stoi;
using std::string;
using std::stringstream;
using std::to_string;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

shouty_stats_service::shouty_stats_service()
    : generator(std::random_device()())
    , distribution(1, 10)
    , revenue_distribution(0, 99999999)
    , customer_id_distribution(1, 1000)
    , revenue_by_customer_id({
        {  1,    "234.50" },
        { 19, "123456.78" },
        { 22, "123456.78" },
        { 57, "123456.78" }
      })
    , latest_eco_stats_month(0)
    , latest_eco_stats_year(0)
{
    if (getenv("VOLATILE_STATS_DATA") != NULL)
    {
        revenue_by_customer_id.clear();
        for (int i = 0; i < 10; i++)
        {
            double random_revenue = revenue_distribution(generator) / 100.0;
            revenue_by_customer_id.insert({
                customer_id_distribution(generator),
                to_string(random_revenue)
            });
        }
    }
}

string shouty_stats_service::get_revenue_for_customer(const std::string & customer_xml) const
{
    check_service_connection();
    int customer_id = get_customer_id(customer_xml);
    auto pos = revenue_by_customer_id.find(customer_id);
    if (pos == revenue_by_customer_id.end())
    {
        const string message("No customer found with ID '"
            + to_string(customer_id)
            + "'");
        throw shouty_stats_service_exception(message);
    }

    stringstream response;
    response << "<CustomerStats id=\""
             << customer_id
             << "\" revenue=\""
             << pos->second
             << "\"/>";
    return response.str();
}

string shouty_stats_service::get_customer_ids() const
{
    stringstream response;
    response << "<Customers>";
    for (auto & customer_data : revenue_by_customer_id)
    {
        response << "<Customer id=\""
                 << customer_data.first
                 << "\"/>";
    }
    response << "</Customers>";
    return response.str();
}

string shouty_stats_service::is_valid_customer(const string & customer_xml) const
{
    int id = get_customer_id(customer_xml);
    if (revenue_by_customer_id.find(id) != revenue_by_customer_id.end())
    {
        return "<booleanResponse result=\"TRUE\" />";
    }
    else
    {
        return "<booleanResponse result=\"FALSE\" />";
    }
}

string shouty_stats_service::get_latest_eco_stats_date() const
{
    stringstream response;

    response << "<LatestEcoStatsDate year=\""
             << latest_eco_stats_year
             << "\" month=\""
             << latest_eco_stats_month
             << "\" />";

    return response.str();
}

void shouty_stats_service::set_eco_stats(const string & eco_stats_xml)
{
    XMLDocument request;
    request.Parse(eco_stats_xml.c_str());
    const XMLElement * root = request.FirstChildElement("EcoStats");
    const int month = stoi(root->Attribute("month"));
    const int year = stoi(root->Attribute("year"));
    auto key = create_key(year, month);

    if (year < latest_eco_stats_year ||
            (year == latest_eco_stats_year && month < latest_eco_stats_month))
    {
        throw shouty_stats_service_exception("EcoStats for a later month have already been set");
    }

    store_eco_stats(key, root->FirstChildElement("EcoStat"));

    latest_eco_stats_year = year;
    latest_eco_stats_month = month;
}

string shouty_stats_service::get_eco_stats_winner_for(const string & date_xml) const
{
    string winners_name = "Nobody";
    double winning_revenue_per_mile = 0;

    XMLDocument request;
    request.Parse(date_xml.c_str());
    const int month = stoi(request.FirstChildElement("EcoStats")->Attribute("month"));
    const int year = stoi(request.FirstChildElement("EcoStats")->Attribute("year"));
    auto key = create_key(year, month);

    auto iterator = eco_stats_store.find(key);
    if (iterator != eco_stats_store.end())
    {
        for (auto & stat : iterator->second)
        {
            if (stat.second > winning_revenue_per_mile)
            {
                winners_name = stat.first;
                winning_revenue_per_mile = stat.second;
            }
        }
    }

    return "<ecoStatsWinner SalespersonName=\"" +
            winners_name +
            "\" />";
}

int shouty_stats_service::get_customer_id(const string & xml) const
{
    XMLDocument request;
    request.Parse(xml.c_str());
    return stoi(request.FirstChildElement("Customer")->Attribute("id"));
}

string shouty_stats_service::create_key(int year, int month) const
{
    stringstream key;
    key << year << "-" << month;
    return key.str();
}

void shouty_stats_service::store_eco_stats(const string & key, const XMLElement * element)
{
    map<string, double> stats;
    while (element != NULL)
    {
        const string name(element->Attribute("salesPersonName"));
        const double rpm(atof(element->Attribute("revenuePerMile")));
        stats[name] = rpm;
        element = element->NextSiblingElement();
    }
    eco_stats_store[key] = stats;
}

void shouty_stats_service::check_service_connection() const
{
    const bool connection_is_reliable = (getenv("RELIABLE_CONNECTION") != NULL);
    if (connection_is_reliable)
    {
        return;
    }
    const int parity_control = distribution(generator);
    if (parity_control == 1)
    {
        const string message =
            "shouty_stats_service connection error - please a wait a few moments and try your request again";
        throw shouty_stats_service_exception(message);
    }
}
