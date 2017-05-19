#ifndef SHOUTY_STATS_SERVICE_INCLUDED
#define SHOUTY_STATS_SERVICE_INCLUDED

#include <map>
#include <random>
#include <string>

namespace tinyxml2
{
    class XMLElement;
}

class shouty_stats_service
{
public:
    shouty_stats_service();
    std::string get_revenue_for_customer(const std::string & customer_xml) const;
    std::string get_customer_ids() const;
    std::string is_valid_customer(const std::string & customer_xml) const;
    std::string get_latest_eco_stats_date() const;
    void set_eco_stats(const std::string & eco_stats_xml);
    std::string get_eco_stats_winner_for(const std::string & date_xml) const;

private:
    void check_service_connection() const;
    void store_eco_stats(const std::string & key, const tinyxml2::XMLElement * root);
    std::string create_key(int year, int month) const;
    int get_customer_id(const std::string & xml) const;

private:
    mutable std::default_random_engine generator;
    mutable std::uniform_int_distribution<int> distribution;
    mutable std::uniform_int_distribution<int> revenue_distribution;
    mutable std::uniform_int_distribution<int> customer_id_distribution;
    std::map<int,std::string> revenue_by_customer_id;

    int latest_eco_stats_month;
    int latest_eco_stats_year;
    mutable std::map<std::string, std::map<std::string, double> > eco_stats_store;
};

#endif
