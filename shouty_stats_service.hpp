#ifndef SHOUTY_STATS_SERVICE_INCLUDED
#define SHOUTY_STATS_SERVICE_INCLUDED

#include "tinyxml2.hpp"
using namespace tinyxml2;

#include <map>
#include <stdexcept>
#include <random>

class shouty_stats_service
{
public:
    shouty_stats_service();
    std::string get_revenue_for_customer(int customer_id) const;
    std::string get_customer_ids() const;
    std::string is_valid_customer(std::string customer_xml) const;
    std::string get_latest_eco_stats_date() const;
    void set_eco_stats(std::string eco_stats_xml);
    std::string get_eco_stats_winner_for(std::string dateXml) const;

private:
    void check_service_connection() const;
    void store_eco_stats(std::string key, const XMLDocument& root);
    std::string create_key(int year, int month) const;

private:
    mutable std::default_random_engine generator;
    mutable std::uniform_int_distribution<int> distribution;
    mutable std::uniform_int_distribution<int> revenue_distribution;
    mutable std::uniform_int_distribution<int> customer_id_distribution;
    std::map<int,double> revenue_by_customer_id;

    int latestEcoStatsMonth;
    int latestEcoStatsYear;
    //mutable std::map<std::string, std::map<std::string, float>> ecoStatsStore;
};

#endif
