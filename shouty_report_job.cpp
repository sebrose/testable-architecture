#include "mileage_claim.hpp"
#include "shouty_report_processor.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<mileage_claim> read_mileage_claims(std::ifstream & ifs)
{
    std::vector<mileage_claim> claims;
    while (ifs.peek() != std::ifstream::traits_type::eof())
    {
        std::string line;
        std::getline(ifs, line);
        std::istringstream iss(line);
        std::string name;
        std::getline(iss, name, ',');
        std::string miles;
        std::getline(iss, miles, ',');
        std::string customer_id;
        std::getline(iss, customer_id, ',');
        mileage_claim claim(name, std::stoi(miles), std::stoi(customer_id));
        claims.push_back(claim);
    }
    return claims;
}

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    const char * filename = argv[1];
    std::ifstream path(filename);
    if (!path.good())
    {
        return 1;
    }

    std::vector<mileage_claim> mileage_claims = read_mileage_claims(path);
    shouty_report_processor job(mileage_claims);
    job.process();
}
