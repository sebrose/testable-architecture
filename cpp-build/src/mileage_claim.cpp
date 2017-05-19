#include "mileage_claim.hpp"

namespace shouty_report
{

mileage_claim::mileage_claim(
    const std::string & name,
    int miles,
    int customer_id
)
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

}
