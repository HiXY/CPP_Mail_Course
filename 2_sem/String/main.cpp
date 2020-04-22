#include "string.hpp"
#include <cstring>
#include <sstream>

bool testConstr ()
{
    String str ("shlyapahooo");
    String str2 (str);
    String str3;
    String str4 (str3);
    return str.size () == 11 && str.size () == str2.size () && !strcmp (str.c_str (), str2.c_str ());
}
bool testErase ()
{
    String str ("anuyuportkazzzzzz");
    str.erase (4, 3);
    return str.erase (2, 3) == "antkazzzzzz" && str.erase () == "";
}
bool testAssign ()
{
    String str ("string"), str2, str3 ("ssss");
    str = str;
    str2 = str;
    str3 = str;
    return str == "string" && str2 == str && str3 == str;
}
bool testAddition ()
{
    String str ("str");
    String s (str);
    for (std::size_t i = 0; i < 20; i++)
        s += s;
    return ("str" + str + str + "str") == "strstrstrstr";
}
bool testPushBack ()
{
    String str;
    for (std::size_t i = 0; i < 4096; i++)
        str.push_back ('a');
    return str == String (4096, 'a');
}
bool testSubstr ()
{
    String str ("maiklelelchls");
    return str.substr (4, 5) == "lelel" && str.substr () == "maiklelelchls";
}
bool testReserve ()
{
    String str;
    str.reserve (1024);
    for (std::size_t i = 0; i < 1024; i++)
        str.push_back ('a');
    str.reserve (2048);
    for (std::size_t i = 0; i < 512; i++)
        str.pop_back ();
    return str == String (512, 'a');
}
bool testFind ()
{
    String str ("heyeyeyeyeyeyeyiyeeyeyeey");
    return str.find ('i') == 15 && str.find ("yeey") == 16 && str.find ("keke") == String::npos;
}
bool testStream ()
{
    std::ostringstream oss;
    oss << String ("wowo") << " " << String ("aps upper");
    std::istringstream iss (oss.str ());
    String anus, psa, yopta;
    iss >> anus >> psa >> yopta;
    return anus == "wowo" && psa == "aps" && yopta == "upper";
}
bool testCStr ()
{
    String str ("wawawaw");
    return str == str.c_str ();
}
char const *testname[] = {"Constructor", "Erase", "Assign", "Add", "Push", "Substr", "Reserve/Pop", "Find", "Stream", "c_str"};
bool (*tests[]) (void) = {testConstr, testErase, testAssign, testAddition, testPushBack, testSubstr, testReserve, testFind, testStream, testCStr};
int main ()
{
    for (std::size_t i = 0; i < sizeof (tests) / sizeof (char *); ++i)
    {
        if (tests[i] ())
            std::cout << "Test " << i + 1 << " (" << testname[i] << "): ok" << std::endl;
        else
            std::cout << "Test " << i + 1 << " (" << testname[i] << "): failed" << std::endl;
    }
}
