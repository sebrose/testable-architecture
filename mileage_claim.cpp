#include "mileage_claim.hpp"
#include <ostream>

mileage_claim::mileage_claim(
    const std::string & name, 
    int miles, 
    int customer_id)
    : name_(name)
    , miles_(miles)
    , customer_id_(customer_id)
{
}

std::string mileage_claim::name() const
{
    return name_;
}

int mileage_claim::miles() const
{
    return miles_;
}

int mileage_claim::customer_id() const
{
    return customer_id_;
}

std::ostream & operator<<(std::ostream & os, const mileage_claim & claim)
{
    os << "name:" << claim.name() << std::endl;
    os << "miles:" << claim.miles() << std::endl;
    os << "cid:" << claim.customer_id() << std::endl;
    return os;
}
