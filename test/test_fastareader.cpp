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

#include "FastaReader.hpp"

using namespace std;

class FastaReaderTestCase : public CppUnit::TestCase
{

    CPPUNIT_TEST_SUITE( FastaReaderTestCase );

    CPPUNIT_TEST( fastafile );
    CPPUNIT_TEST_EXCEPTION( fastafile_donotexist, std::invalid_argument );
    CPPUNIT_TEST_EXCEPTION( fastafile_directory, std::invalid_argument );

    CPPUNIT_TEST_SUITE_END();

    void fastafile ();

    void fastafile_donotexist();

    void fastafile_directory();

};


CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( FastaReaderTestCase, "FastaReaderTestCase" );

// register test suite
CppUnit::Test *suite()
{
    CppUnit::TestFactoryRegistry &registry =
        CppUnit::TestFactoryRegistry::getRegistry();
    registry.registerFactory(
        &CppUnit::TestFactoryRegistry::getRegistry( "FastaReaderTestCase" ) );
    return registry.makeTest();
}


// test cases for fastafile

// fastafile: valid file
void FastaReaderTestCase::fastafile ()
{
    // empty file
    FastaReader empty("data/noseq.fa");
    while(empty.hasNextSequence()) {
        empty.readSequence();
        CPPUNIT_FAIL("just EOF,hasNextSequence() did not return false... ");
    }
    // file with three records
    FastaReader threeseq("data/threeseq.fa");
    unsigned int seqnum = 0;
    while(threeseq.hasNextSequence()) {
        seqnum++;
        threeseq.readSequence();
        if(1 == seqnum) {
            std::string id = threeseq.Id();
            std::string description = threeseq.Description();
            std::string sequence = threeseq.Sequence();
            CPPUNIT_ASSERT(0 == id.compare("test"));
            CPPUNIT_ASSERT(0 == description.compare("id description"));
            CPPUNIT_ASSERT(0 == sequence.compare(""));
            CPPUNIT_ASSERT(0 == threeseq.SequenceLength());
        }
        if(2 == seqnum) {
            std::string id = threeseq.Id();
            std::string description = threeseq.Description();
            std::string sequence = threeseq.Sequence();
            CPPUNIT_ASSERT(0 == id.compare("test"));
            CPPUNIT_ASSERT(0 == description.compare("bad char"));
            CPPUNIT_ASSERT(0 == sequence.compare("acgt"));
            CPPUNIT_ASSERT(4 == threeseq.SequenceLength());
        }
        if(3 == seqnum) {
            std::string id = threeseq.Id();
            std::string description = threeseq.Description();
            std::string sequence = threeseq.Sequence();
            CPPUNIT_ASSERT(0 == id.compare("test"));
            CPPUNIT_ASSERT(0 == description.compare("eof"));
            CPPUNIT_ASSERT(0 == sequence.compare("acgtnnn"));
            CPPUNIT_ASSERT(7 == threeseq.SequenceLength());
        }
    }
}




// fastafile: test file that do no exist
void FastaReaderTestCase::fastafile_donotexist()
{
    FastaReader f("data/ does not exist...");
}

// fastafile: test directory
void FastaReaderTestCase::fastafile_directory()
{
    FastaReader f("data");
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
        std::cout << "Unit test for FastaReader class " << std::endl;
        std::cout << "========================="  << std::endl;
        runner.run( controller, testPath );
        std::cout << "=========================" << std::endl;
        std::cout << std::endl;
        // Print test in XML and compiler compatible format.
        std::ofstream xmlFileOut("Test_fastareader.UnitTests.xml");
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

