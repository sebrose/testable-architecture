#ifndef MILEAGE_CLAIM_BUILDER_INCLUDED
#define MILEAGE_CLAIM_BUILDER_INCLUDED

#include "mileage_claim.hpp"
#include <string>

class mileage_claim_builder
{
public:
    mileage_claim build() const;
    
    mileage_claim_builder & with_sales_person(const std::string & value);
    mileage_claim_builder & with_miles(int value);
    mileage_claim_builder & with_customer_id(int value);
    
private:
    std::string sales_person_name;
    int miles;
    int customer_id;
};


#endif
