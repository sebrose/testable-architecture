#include "fake_stats_service.hpp"
#include "shouty_stats_service_exception.hpp"
#include <sstream>
#include <vector>

using std::string;
using std::stod;
using std::stoi;
using std::stringstream;
using std::to_string;
using std::vector;

namespace {
    
vector<string> split(const string & s, char delimiter)
{
    vector<string> tuples;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter))
    {
        tuples.push_back(token);
    }
    return tuples;
}

string quoted(const string & s)
{
    return "'" + s + "'";
}
    
} // namespace

fake_stats_service::fake_stats_service(const std::string & data)
{
    const vector<string> tuples = split(data, ';');
    for (auto & tuple : tuples)
    {
        const vector<string> pair = split(tuple, ',');
        const int customer_id = stoi(pair[0]);
        const double revenue = stod(pair[1]);
        revenue_data[customer_id] = revenue;
    }
}

double fake_stats_service::get_revenue(int customer_id) const
{
    auto it = revenue_data.find(customer_id);
    if (it != revenue_data.end())
    {
    	return it->second;
    }
    else
    {
        const string message("No customer found with ID "
    		+ quoted(to_string(customer_id)));
    	throw shouty_stats_service_exception(message);
    }
}
