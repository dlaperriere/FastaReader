#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextTestProgressListener.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Utils.hpp"

using namespace std;

class UtilsTestCase : public CppUnit::TestCase
{


    CPPUNIT_TEST_SUITE( UtilsTestCase );

    CPPUNIT_TEST( str2double );
    CPPUNIT_TEST_EXCEPTION( str2double_empty, std::invalid_argument );
    CPPUNIT_TEST_EXCEPTION( str2double_notnumber, std::invalid_argument );

    CPPUNIT_TEST( is_directory );

    CPPUNIT_TEST( str2uppercase );
    CPPUNIT_TEST( str_keep_alpha );
    CPPUNIT_TEST( str_replace_char );
    CPPUNIT_TEST( str_joinc );
    CPPUNIT_TEST( str_splitc );
    CPPUNIT_TEST( str_joins );
    CPPUNIT_TEST( str_splits );

    CPPUNIT_TEST_SUITE_END();

    Utils u;

    void str2double ();
    void str2double_empty();
    void str2double_notnumber();

    void is_directory();

    void str2uppercase();
    void str_keep_alpha();
    void str_replace_char();
    void str_joinc();
    void str_splitc();
    void str_joins();
    void str_splits();

public:


    void setUp ();
};


CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( UtilsTestCase, "UtilsTestCase" );


// create Utils object
void UtilsTestCase::setUp ()
{
    u = Utils();
}


// register test suite
CppUnit::Test *suite()
{
    CppUnit::TestFactoryRegistry &registry =
        CppUnit::TestFactoryRegistry::getRegistry();
    registry.registerFactory(
        &CppUnit::TestFactoryRegistry::getRegistry( "UtilsTestCase" ) );
    return registry.makeTest();
}


// str2double: test convertion of a valid string
void UtilsTestCase::str2double ()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL (u.str2double("0.0"), 0.0, 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL (u.str2double("1"), 1.0, 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL (u.str2double("2.0"), 2.0, 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL (u.str2double("-2.0"), -2.0, 0.1);
}


// str2double: test convertion of an empty string
void UtilsTestCase::str2double_empty()
{
    u.str2double("");
}

// str2double: test convertion of a string that is not a number
void UtilsTestCase::str2double_notnumber()
{
    u.str2double("this is NOT a number :-) 1.0");
}


// test cases for is_directory
void UtilsTestCase::is_directory()
{
    // directory
    CPPUNIT_ASSERT( true == u.is_directory("data") );
    CPPUNIT_ASSERT( true == u.is_directory(".") );
    CPPUNIT_ASSERT( true == u.exists("data") );
    CPPUNIT_ASSERT( true == u.exists(".") );
    // file
    CPPUNIT_ASSERT( false == u.is_directory("data/file") );
    CPPUNIT_ASSERT( true == u.exists("data/file") );
    // garbage (not a file or directory)
    CPPUNIT_ASSERT( false == u.exists("") );
    CPPUNIT_ASSERT( false == u.exists(" ") );
    CPPUNIT_ASSERT( false == u.exists(" this is NOT a directory") );
    CPPUNIT_ASSERT( false == u.exists("-42-") );
}

// test cases for str2uppercase
void UtilsTestCase::str2uppercase()
{
    std::string lower = "qwertyuiopasdfghjklzxcvbnm -1234567890";
    std::string upper = "QWERTYUIOPASDFGHJKLZXCVBNM -1234567890";
    CPPUNIT_ASSERT( 0 == upper.compare(u.str2uppercase("qwertyuiopasdfghjklzxcvbnm -1234567890") ) );
    std::string l2u = u.str2uppercase(lower);
    CPPUNIT_ASSERT( 0 == l2u.compare(upper));
    CPPUNIT_ASSERT( 0 == upper.compare(u.str2uppercase(lower) ) );
    std::string u2u = u.str2uppercase(upper);
    CPPUNIT_ASSERT(0 == u2u.compare(upper));
    CPPUNIT_ASSERT( 0 == upper.compare(u.str2uppercase(upper) ) );
}

// test cases for str_keep_alpha
void UtilsTestCase::str_keep_alpha()
{
    std::string lower  = "qwertyuiopasdfghjklzxcvbnm -1234567890 ~ \t\n\b - | ,.{}[]@!$%^&*()<> :-)";
    std::string alower = "qwertyuiopasdfghjklzxcvbnm";
    CPPUNIT_ASSERT( 0 == alower.compare(u.str_keep_alpha(lower) ) );
    std::string upper  = "QWERTYUIOPASDFGHJKLZXCVBNM -1234567890  \t\n\b ~ \t\n\b - | ,.{}[]@!$%^&*()<> :-)";
    std::string aupper = "QWERTYUIOPASDFGHJKLZXCVBNM";
    CPPUNIT_ASSERT( 0 == aupper.compare(u.str_keep_alpha(upper) ) );
    std::string empty;
    CPPUNIT_ASSERT( 0 == empty.compare(u.str_keep_alpha("") ) );
    CPPUNIT_ASSERT( 0 == empty.compare(u.str_keep_alpha(" ") ) );
    CPPUNIT_ASSERT( 0 == empty.compare(u.str_keep_alpha(" ~ \t\n\b - | ,.{}[]@!$%^&*()<> :-)") ) );
}

// test cases for str_replace_char
void UtilsTestCase::str_replace_char()
{
    std::string lower  = "qwertyuiopasdfghjklzxcvbnm -1234567890 ~ \t\n\b - | ,.{}[]@!$%^&*()<> :-)";
    std::string rlower = "qwertyuiopasdfghjklzxcvbnm_-1234567890_~_\t\n\b_-_|_,.{}[]@!$%^&*()<>_:-)";
    CPPUNIT_ASSERT( 0 == rlower.compare(u.str_replace_char(lower,' ','_') ) );
    std::string upper  = "QWERTYUIOPASDFGHJKLZXCVBNM -1234567890  \t\n\b ~ \t\n\b - | ,.{}[]@!$%^&*()<> :-)";
    std::string rupper = "QWERTYUIOPASDFGHJKLZXCVBNM_-1234567890__\t\n\b_~_\t\n\b_-_|_,.{}[]@!$%^&*()<>_:-)";
    CPPUNIT_ASSERT( 0 == rupper.compare(u.str_replace_char(upper,' ','_'))  );
    std::string empty;
    CPPUNIT_ASSERT( 0 == empty.compare(u.str_replace_char("",' ','a') ) );
    std::string space = " ";
    CPPUNIT_ASSERT( 0 == space.compare(u.str_replace_char(" ",' ',' ') ) );
}

// test cases for join char delim
void UtilsTestCase::str_joinc()
{
    std::vector<string> testv1_join = {"a"};
    auto testv1_joined = u.join(testv1_join,'-');
    CPPUNIT_ASSERT(0 == testv1_joined.compare("a") );

    std::vector<string> testv3_join = {"a","b","c"};
    auto testv3_joined = u.join(testv3_join,'-');
    CPPUNIT_ASSERT(0 == testv3_joined.compare("a-b-c") );
}

// test cases for split char delim
void UtilsTestCase::str_splitc()
{
    auto test_split1 = u.split("a",'-');
    CPPUNIT_ASSERT(1 == test_split1.size() );
    CPPUNIT_ASSERT(0 == test_split1[0].compare("a") );

    auto test_split3 = u.split("a-b-c",'-');
    CPPUNIT_ASSERT(3 == test_split3.size() );
    CPPUNIT_ASSERT(0 == test_split3[0].compare("a") );
    CPPUNIT_ASSERT(0 == test_split3[1].compare("b") );
    CPPUNIT_ASSERT(0 == test_split3[2].compare("c") );

    auto test_split4 = u.split("a-b--c",'-');
    CPPUNIT_ASSERT(4 == test_split4.size() );
    CPPUNIT_ASSERT(0 == test_split4[0].compare("a") );
    CPPUNIT_ASSERT(0 == test_split4[1].compare("b") );
    CPPUNIT_ASSERT(0 == test_split4[2].compare("") );
    CPPUNIT_ASSERT(0 == test_split4[3].compare("c") );
}


// test cases for join string delim
void UtilsTestCase::str_joins()
{
    std::string delim(";-");

    std::vector<string> testv1_join = {"a"};
    auto testv1_joined = u.join(testv1_join,delim);
    CPPUNIT_ASSERT(0 == testv1_joined.compare("a") );

    std::vector<string> testv3_join = {"a","b","c"};
    auto testv3_joined = u.join(testv3_join,delim);
    CPPUNIT_ASSERT(0 == testv3_joined.compare("a;-b;-c") );
}

// test cases for split string delim
void UtilsTestCase::str_splits()
{
    std::string delim("-");
    auto test_split1 = u.split("a",delim);
    CPPUNIT_ASSERT(1 == test_split1.size() );
    CPPUNIT_ASSERT(0 == test_split1[0].compare("a") );

    auto test_split3 = u.split("a-b-c",delim);
    CPPUNIT_ASSERT(3 == test_split3.size() );
    CPPUNIT_ASSERT(0 == test_split3[0].compare("a") );
    CPPUNIT_ASSERT(0 == test_split3[1].compare("b") );
    CPPUNIT_ASSERT(0 == test_split3[2].compare("c") );

    auto test_split4 = u.split("a-b--c",delim);
    CPPUNIT_ASSERT(4 == test_split4.size() );
    CPPUNIT_ASSERT(0 == test_split4[0].compare("a") );
    CPPUNIT_ASSERT(0 == test_split4[1].compare("b") );
    CPPUNIT_ASSERT(0 == test_split4[2].compare("") );
    CPPUNIT_ASSERT(0 == test_split4[3].compare("c") );
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN
int main( int argc, char* argv[] )
{
    std::string testPath = (argc > 1) ? std::string(argv[1]) : "";
    // Create the event manager and test controller
    CppUnit::TestResult controller;
    // Add a listener that colllects test result
    CppUnit::TestResultCollector result;
    controller.addListener( &result );
    // Add a listener that print dots as test run.
    //CppUnit::TextTestProgressListener progress;
    // Add a listener that print name of methods as test run.
    CppUnit::BriefTestProgressListener progress;
    controller.addListener( &progress );
    // Add the top suite to the test runner
    CppUnit::TestRunner runner;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
    runner.addTest( suite() );
    try {
        std::cout  << std::endl;
        std::cout << "Unit test for Utils class " << std::endl;
        std::cout << "========================="  << std::endl;
        runner.run( controller, testPath );
        std::cout << "=========================" << std::endl;
        std::cout << std::endl;
        // Print test in XML and compiler compatible format.
        std::ofstream xmlFileOut("Test_utils.UnitTests.xml");
        CppUnit::XmlOutputter xmloutputter( &result, xmlFileOut );
        CppUnit::CompilerOutputter outputter( &result, std::cerr );
        xmloutputter.write();
        outputter.write();
    } catch ( std::invalid_argument& e ) { // Test path not resolved
        std::cerr  <<  std::endl
                   <<  "ERROR: "  <<  e.what()
                   << std::endl;
        return 0;
    }
    return result.wasSuccessful() ? 0 : 1;
}



