#include "mileage_claim_collection_builder.hpp"

namespace shouty_report
{
const std::vector<mileage_claim>
mileage_claim_collection_builder::default_mileage_claim_collection = {
      mileage_claim("David Allen", 130000, 57),
      mileage_claim("Lisa Crispin", 27000, 19),
      mileage_claim("Ian Dees", 19238855, 22)
};

std::vector<mileage_claim> mileage_claim_collection_builder::build() const
{
    if (mileage_claim_collection.size() == 0)
    {
        return default_mileage_claim_collection;
    }
    else
    {
        return mileage_claim_collection;
    }
}

mileage_claim_collection_builder &
mileage_claim_collection_builder::with_sales_person_miles_for_customer(
    const std::string & name,
    const int miles,
    const int id
)
{
    mileage_claim_collection.push_back(mileage_claim(name, miles, id));
    return *this;
}

}
