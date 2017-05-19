#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <map>

#include <tinyxml2.hpp>

using std::back_inserter;
using std::cerr;
using std::copy;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::map;
using std::string;
using std::system;
using std::vector;
using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;

namespace {

string test_data_path = "test/";

int run(const string & input_filename, string environment_variables = string())
{
    // environment_variables += std::string(
    //    " FAKE_INITIALISATION_DATA='19,123456.78;22,123456.78;57,123456.78'"
    //);

    string command = environment_variables + " ./shouty_report_job "
        + test_data_path + input_filename;
    return system(command.c_str());
}

string read_file(const string & path)
{
    std::ifstream file(path);
    std::string str;
    std::string file_contents;
    while (std::getline(file, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }

    return file_contents;
}

vector<map<string, string>> document_to_list_of_maps(XMLDocument const & document)
{
    vector<map<string, string>> result;

    const XMLElement * root = document.FirstChildElement();
    const XMLElement * child = root->FirstChildElement();

    while (child != NULL)
    {
        map<string, string> attributes;
        const XMLAttribute * attr = child->FirstAttribute();
        while (attr != NULL)
        {
            attributes[attr->Name()] = attr->Value();
            attr = attr->Next();
        }

        result.push_back(attributes);

        child = child->NextSiblingElement();
    }

    return result;
}

bool are_equal(
    vector<map<string, string>> const & actual,
    vector<map<string, string>> const & expected
)
{
    if (actual.size() != expected.size())
    {
        return false;
    }

    vector<map<string, string>>::const_iterator it;
    for (it = actual.begin(); it != actual.end(); ++it)
    {
        if (std::find(expected.begin(), expected.end(), *it) == expected.end())
        {
            return false;
        }
    }

    return true;
}

void assert_xml_equal(
    const char * test_name,
    const string & expected_path,
    const string & actual_path
)
{
    auto actual_txt = read_file(actual_path);
    XMLDocument actual_doc;
    actual_doc.Parse(actual_txt.c_str());
    vector<map<string, string>> actual
        = document_to_list_of_maps(actual_doc);


    auto expected_txt = read_file(test_data_path + expected_path);
    XMLDocument expected_doc;
    expected_doc.Parse(expected_txt.c_str());
    vector<map<string, string>> expected
        = document_to_list_of_maps(expected_doc);

    if (!are_equal(actual, expected))
    {
        cerr << test_name << std::endl
            << "Expected XML to contain:" << std::endl
            << expected_txt << std::endl
            << "but actually got:" << std::endl
            << actual_txt << std::endl;

        assert(false);
    }
}

void single_sales_person()
{
    assert(run("test_case_1_input.csv") == 0);
    assert(system("test -e ./report.xml") == 0);
    const char * expected_filename = "test_case_1_expected.xml";
    const char * actual_filename = "report.xml";
    assert_xml_equal(__FUNCTION__, expected_filename, actual_filename);
}

void multiple_sales_people()
{
    assert(run("test_case_2_input.csv") == 0);
    assert(system("test -e ./report.xml") == 0);
    const char * expected_filename = "test_case_2_expected.xml";
    const char * actual_filename = "report.xml";
    assert_xml_equal(__FUNCTION__, expected_filename, actual_filename);
}

} // namespace

int main()
{
    single_sales_person();
    multiple_sales_people();

    cout << "tests (end2end) passed" << endl;
}
