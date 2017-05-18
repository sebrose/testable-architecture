#ifndef MILEAGE_CLAIM_COLLECTION_BUILDER_INCLUDED
#define MILEAGE_CLAIM_COLLECTION_BUILDER_INCLUDED

#include "mileage_claim.hpp"
#include <string>
#include <vector>

namespace shouty_report
{

class mileage_claim_collection_builder
{
public:
    std::vector<mileage_claim> build() const;

    mileage_claim_collection_builder & with_sales_person_miles_for_customer(
        const std::string & name,
        const int miles,
        const int id
    );

private:
    const static std::vector<mileage_claim> default_mileage_claim_collection;
    std::vector<mileage_claim> mileage_claim_collection;
};

}

#endif
