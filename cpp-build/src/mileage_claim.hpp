#ifndef MILEAGE_CLAIM_INCLUDED
#define MILEAGE_CLAIM_INCLUDED

#include <string>

namespace shouty_report
{

class mileage_claim
{
public:
    mileage_claim(const std::string & name, int miles, int customer_id);
    std::string name() const;
    int miles() const;
    int customer_id() const;
private:
    std::string name_;
    int miles_;
    int customer_id_;
};

}
#endif
