#include "mileage_claim.hpp"
#include "shouty_report_processor.hpp"
//#include "stats_service.hpp"
//#include "production_stats_service.hpp"
//#include "../test/fake_stats_service.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::getline;
using std::ifstream;
using std::istringstream;
using std::stoi;
using std::string;
using std::vector;
using namespace shouty_report;

vector<mileage_claim> read_mileage_claims(ifstream & ifs)
{
    vector<mileage_claim> claims;
    while (ifs.peek() != ifstream::traits_type::eof())
    {
        string line;
        getline(ifs, line);
        istringstream iss(line);
        string name;
        getline(iss, name, ',');
        string miles;
        getline(iss, miles, ',');
        string customer_id;
        getline(iss, customer_id, ',');
        mileage_claim claim(name, stoi(miles), stoi(customer_id));
        claims.push_back(claim);
    }
    return claims;
}

/*
std::unique_ptr<stats_service> create_stats_service()
{
    const char * initialisation_data = std::getenv("FAKE_INITIALISATION_DATA");
    if (initialisation_data != NULL)
        return std::make_unique<fake_stats_service>(
            initialisation_data
        );
    else
        return std::make_unique<production_stats_service>();
}
*/

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        return EXIT_FAILURE;
    }

    const char * filename = argv[1];
    ifstream path(filename);
    if (!path.good())
    {
        return EXIT_FAILURE;
    }

    vector<mileage_claim> mileage_claims = read_mileage_claims(path);
    shouty_report_processor job(mileage_claims);
    job.process();
    return EXIT_SUCCESS;
}
