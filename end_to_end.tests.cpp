
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace {

int run(std::string input_filename, std::string environment_variables = std::string())
{
  environment_variables += std::string(" TESTING=true");

  std::string command = environment_variables + std::string(" ./shouty_report_job ") + input_filename;
  return system(command.c_str());
}

std::vector<std::string> read_lines(const char * filename)
{
    std::vector<std::string> lines;
    std::ifstream ifs(filename);
    while (ifs.peek() != std::ifstream::traits_type::eof())
    {
        std::string line;
        std::getline(ifs, line);
        lines.push_back(line);
    }
    return lines;
}

void assert_equal_files(
    const char * expected_filename,
    const char * actual_filename)
{
    std::vector<std::string> expected = read_lines(expected_filename);
    std::vector<std::string> actual = read_lines(actual_filename);
    assert(expected.size() == actual.size());

    for (size_t i = 0; i != expected.size(); ++i)
    {
        const std::string lhs = expected[i];
        const std::string rhs = actual[i];
        if (lhs != rhs)
        {
            std::cerr << "expected[" << i << "] == :" << lhs << ':' << std::endl;
            std::cerr << "  actual[" << i << "] == :" << rhs << ':' << std::endl;
            assert(false);
        }
    }
}

void single_sales_person()
{
    assert(run("test_case_1_input.csv") == 0);
    assert(system("test -e ./report.xml") == 0);
    const char * expected_filename = "test_case_1_expected.xml";
    const char * actual_filename = "report.xml";
    assert_equal_files(expected_filename, actual_filename);
}

void multiple_sales_people()
{
    assert(run("test_case_2_input.csv") == 0);
    assert(system("test -e ./report.xml") == 0);
    const char * expected_filename = "test_case_2_expected.xml";
    const char * actual_filename = "report.xml";
    assert_equal_files(expected_filename, actual_filename);
}

} // namespace

int main()
{
    single_sales_person();
    multiple_sales_people();
    std::cout << "tests (end2end) passed" << std::endl;
}
