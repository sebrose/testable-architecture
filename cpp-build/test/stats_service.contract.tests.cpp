#include <cassert>
#include <iostream>

namespace {

  void production_returns_revenue_for_valid_customer_id()
  {
  }

  void production_throws_exception_for_invalid_customer_id()
  {
  }

} // namespace


int main()
{
    production_returns_revenue_for_valid_customer_id();
    production_throws_exception_for_invalid_customer_id();

    std::cout << "tests (contract) passed" << std::endl;
}
