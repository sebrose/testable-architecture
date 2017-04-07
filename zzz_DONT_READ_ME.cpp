#include "shouty_stats_service.hpp"
#include "shouty_stats_service_exception.hpp"

#include <sstream>
#include <iomanip>

shouty_stats_service::shouty_stats_service()
    : generator(std::random_device()())
    , distribution(1,10)
    , revenue_distribution(0, 99999999)
    , customer_id_distribution(1, 1000)
    , revenue_by_customer_id({
        {  1,    234.50 },
        { 19, 123456.78 },
        { 22, 123456.78 },
        { 57, 123456.78 }
      })
{
  if (std::getenv("VOLATILE_STATS_DATA") != NULL)
  {
     revenue_by_customer_id = std::map<int,double>();
     for (int i=0; i<10; i++)
     {
         revenue_by_customer_id.insert({customer_id_distribution(generator), ((double)(revenue_distribution(generator)))/100.0});
     }
 }
}

std::string shouty_stats_service::get_revenue_for_customer(int customer_id) const
{
    check_service_connection();
    auto pos = revenue_by_customer_id.find(customer_id);
    if (pos == revenue_by_customer_id.end())
    {
        const std::string message("No customer found with ID '"
            + std::to_string(customer_id)
            + "'");
        throw shouty_stats_service_exception(message);
    }

    std::stringstream response;
    response << "<CustomerStats id=\""
             << customer_id
             << "\" revenue=\""
             << std::setprecision(7) << pos->second
             << "\"/>";
    return response.str();
}

std::string shouty_stats_service::get_customer_ids() const
{
  std::stringstream response;
  response << "<Customers>";

  for (auto && customer_data : revenue_by_customer_id)
  {
      response
        << "<Customer id=\""
        << customer_data.first
        << "\"/>";
  }

  response << "</Customers>";

  return response.str();
}

std::string shouty_stats_service::is_valid_customer(std::string customer_xml) const
{
  XMLDocument request;
  request.Parse(customer_xml.c_str());
  int id = atoi(request.FirstChildElement("Customer")->Attribute("id"));

  if (revenue_by_customer_id.find(id) != revenue_by_customer_id.end())
  {
      return "<booleanResponse result=\"TRUE\" />";
  }
  else
  {
      return "<booleanResponse result=\"FALSE\" />";
  }
}

std::string shouty_stats_service::get_latest_eco_stats_date() const
{
  std::stringstream response;

  response
    << "<LatestEcoStatsDate year=\""
    << latestEcoStatsYear
    << "\" month=\""
    << latestEcoStatsMonth
    << "\" />";

  return response.str();
}

void shouty_stats_service::set_eco_stats(std::string eco_stats_xml)
{
    XMLDocument request;
    request.Parse(eco_stats_xml.c_str());
    int month = atoi(request.FirstChildElement("Date")->Attribute("month"));
    int year = atoi(request.FirstChildElement("Date")->Attribute("year"));

    auto key = create_key(year, month);

    if (year < latestEcoStatsYear ||
            (year == latestEcoStatsYear && month < latestEcoStatsMonth))
    {
        throw new shouty_stats_service_exception("EcoStats for a later month have already been set");
    }

    store_eco_stats(key, request);
    latestEcoStatsYear = year;
    latestEcoStatsMonth = month;
}

std::string shouty_stats_service::get_eco_stats_winner_for(std::string dateXml) const
{
    std::string winnersName = "Nobody";
    // double winning_revenue_per_mile = 0;

    XMLDocument request;
    request.Parse(dateXml.c_str());
    int month = atoi(request.FirstChildElement("Date")->Attribute("month"));
    int year = atoi(request.FirstChildElement("Date")->Attribute("year"));

    auto key = create_key(year, month);


    // for (auto && stat : eco_stats_store.find[key])
    // {
    //     if (stat.Value > winningRevenuePerMile)
    //     {
    //         winnersName = stat.Key;
    //         winningRevenuePerMile = stat.Value;
    //     }
    // }

    return "<ecoStatsWinner SalesPersonName=\"" +
            winnersName +
            "\" />";
}

std::string shouty_stats_service::create_key(int year, int month) const
{
  std::stringstream key;
  key << year << "-" << month;
  return key.str();
}

void shouty_stats_service::store_eco_stats(std::string , const XMLDocument& )
  {
      // if (root.HasChildNodes)
      // {
      //     var ecoStats = new Dictionary<string, float>();
      //
      //     XmlNode ecoStatNode = root.FirstChild;
      //
      //     while (ecoStatNode != null)
      //     {
      //         ecoStats[ecoStatNode.Attributes["SalesPersonName"].Value] = float.Parse(ecoStatNode.Attributes["RevenuePerMile"].Value);
      //         ecoStatNode = ecoStatNode.NextSibling;
      //     }
      //
      //     ecoStatsStore[key] = ecoStats;
      // }
  }

void shouty_stats_service::check_service_connection() const
{
    bool connectionIsReliable = (std::getenv("RELIABLE_CONNECTION") != NULL);

    if (connectionIsReliable)
    {
      return;
    }

    int parity_control = distribution(generator);
    if (parity_control == 1)
    {
        const std::string message =
            "shouty_stats_service connection error - please a wait a few moments and try your request again";
        throw shouty_stats_service_exception(message);
    }
}


shouty_stats_service_exception::shouty_stats_service_exception(
    const std::string & message
)
    : std::runtime_error(message)
{
}
