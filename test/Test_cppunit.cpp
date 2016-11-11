#include <fstream>
#include <iostream>

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

#include "Money.h"

class MoneyTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( MoneyTest );
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testEqual );
    CPPUNIT_TEST( testAdd );
    CPPUNIT_TEST_EXCEPTION( testAddThrow, IncompatibleMoneyError );
    CPPUNIT_TEST_SUITE_END();

public:

    void testConstructor();
    void testEqual();
    void testAdd();
    void testAddThrow();
};

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( MoneyTest );

void
MoneyTest::testConstructor()
{
    // Set up
    const std::string currencyFF( "FF" );
    const double longNumber = 12345678.90123;

    // Process
    Money money( longNumber, currencyFF );

    // Check
    CPPUNIT_ASSERT_EQUAL( longNumber, money.getAmount() );
    CPPUNIT_ASSERT_EQUAL( currencyFF, money.getCurrency() );
}

void
MoneyTest::testEqual()
{
    // Set up
    const Money money123FF( 123, "FF" );
    const Money money123USD( 123, "USD" );
    const Money money12FF( 12, "FF" );
    const Money money12USD( 12, "USD" );

    // Process & Check
    CPPUNIT_ASSERT( money123FF == money123FF );     // ==
    CPPUNIT_ASSERT( money12FF != money123FF );      // != amount
    CPPUNIT_ASSERT( money123USD != money123FF );    // != currency
    CPPUNIT_ASSERT( money12USD != money123FF );    // != currency and != amount
}

void
MoneyTest::testAdd()
{
    // Set up
    const Money money12FF( 12, "FF" );
    const Money expectedMoney( 135, "FF" );

    // Process
    Money money( 123, "FF" );
    money += money12FF;

    // Check
    CPPUNIT_ASSERT_EQUAL( expectedMoney.getAmount()  , money.getAmount() );  // += works
    CPPUNIT_ASSERT( &money == &(money += money12FF) );           // += returns ref. on 'this'.
}

void
MoneyTest::testAddThrow()
{
    // Set up
    const Money money123FF( 123, "FF" );

    // Process
    Money money( 123, "USD" );
    money += money123FF;        // should throw an exception
}


/****************************************************************************/

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( MoneyTest, "test_money_cppunit" );

// register test suite
CppUnit::Test *suite()
{
    CppUnit::TestFactoryRegistry &registry =
        CppUnit::TestFactoryRegistry::getRegistry();
    registry.registerFactory(
        &CppUnit::TestFactoryRegistry::getRegistry( "test_money_cppunit" ) );
    return registry.makeTest();
}


int main(int argc, char* argv[])
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
        std::cout << "test Money class with cppunit" << std::endl;
        std::cout << "========================="  << std::endl;
        runner.run( controller, testPath );
        std::cout << "=========================" << std::endl;
        std::cout << std::endl;
        // Print test in XML and compiler compatible format.
        std::ofstream xmlFileOut("Test_cppunit.UnitTests.xml");
        CppUnit::XmlOutputter xmloutputter( &result, xmlFileOut);
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


