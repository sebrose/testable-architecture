#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using std::back_inserter;
using std::cerr;
using std::copy;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::string;
using std::system;
using std::vector;

namespace {

int run(const string & input_filename, string environment_variables = string())
{
    environment_variables += string(" ENVIRONMENT_VARIABLE=value");

    string command = environment_variables + " ./shouty_report_job " 
        + input_filename;
    return system(command.c_str());
}

struct line
{
    string value;
	operator string() const 
    { 
        return value; 
    } 
};
    
istream & operator>>(istream & is, line & in)
{   
    return getline(is, in.value);
}
    
vector<string> read_file(const char * filename)
{    
    vector<string> lines;
    ifstream ifs(filename);
    copy(istream_iterator<line>(ifs), {}, back_inserter(lines));
    return lines;
}

void print_file(const char * ae, 
                const char * filename, 
                const vector<string> & lines)
{
    cerr << endl;
    cerr << ae << "_filename: " << filename << endl;
    cerr << ae << "_filename.line_count: " << lines.size() << endl;
    cerr << ae << "..." << endl;
    for (auto & line : lines)
        cerr << "    " << line << endl;    
    cerr << endl;
}
    
void assert_equal_files(
    const char * test_name,
    const char * expected_filename,
    const char * actual_filename)
{    
    vector<string> expected = read_file(expected_filename);
    vector<string>   actual = read_file(  actual_filename);
    if (expected.size() != actual.size()) 
    {    
        cerr << test_name << std::endl;
        print_file("expected", expected_filename, expected);
        print_file(  "actual",   actual_filename,   actual);        
        assert(false);
    }

    for (size_t i = 0; i != expected.size(); ++i)
    {
        const string lhs = expected[i];
        const string rhs =   actual[i];
        if (lhs != rhs)
        {
            cerr << test_name << endl;
            cerr << "expected_filename: " << expected_filename << endl;
            cerr << "  actual_filename: " <<   actual_filename << endl;
            cerr << "expected[" << i << "] == :" << lhs << ':' << endl;
            cerr << "  actual[" << i << "] == :" << rhs << ':' << endl;
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
    assert_equal_files(__FUNCTION__, expected_filename, actual_filename);
}

void multiple_sales_people()
{
    assert(run("test_case_2_input.csv") == 0);
    assert(system("test -e ./report.xml") == 0);
    const char * expected_filename = "test_case_2_expected.xml";
    const char * actual_filename = "report.xml";
    assert_equal_files(__FUNCTION__, expected_filename, actual_filename);
}

} // namespace

int main()
{
    single_sales_person();
    multiple_sales_people();

    cout << "tests (end2end) passed" << endl;
}
