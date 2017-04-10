#ifndef SHOUTY_REPORT_PROCESSOR
#define SHOUTY_REPORT_PROCESSOR

#include "mileage_claim.hpp"
#include "shouty_stats_service.hpp"
#include <memory>
#include <vector>

class shouty_report_processor
{
public:
    explicit shouty_report_processor(const std::vector<mileage_claim> &);
    void process() const;

private:
    std::vector<mileage_claim> claims_;
    std::unique_ptr<shouty_stats_service> stats_service_;
};

#endif
