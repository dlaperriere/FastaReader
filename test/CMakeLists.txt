cmake_minimum_required(VERSION 3.3)

project(FastaReaderUnitTest CXX)


# look for cppunit
if( NOT CMAKE_MODULE_PATH )
    set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cppunit/cmake_modules)
endif()

include( FindCPPUNIT )


# download & build cppunit
if( NOT CPPUNIT_FOUND )

   configure_file( ${CMAKE_MODULE_PATH}/DownloadCPPUNIT.cmake.in ${CMAKE_BINARY_DIR}/cppunit-download/CMakeLists.txt )
   
   MESSAGE(STATUS "Downloading CppUnit")   
   execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cppunit-download )
     
   execute_process(COMMAND ${CMAKE_COMMAND} --build . 
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cppunit-download )
   
   MESSAGE(STATUS "cmake CppUnit for ${CMAKE_GENERATOR}")      
   execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cppunit-src)
   
   IF(${CMAKE_GENERATOR} MATCHES "Visual Studio")
     MESSAGE(STATUS "Build debug version of CppUnit")     
     execute_process(COMMAND ${CMAKE_COMMAND} --build . --target cppunit --config Debug
       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cppunit-src )
   ENDIF(${CMAKE_GENERATOR} MATCHES "Visual Studio")
   
   MESSAGE(STATUS "Build release version of CppUnit")        
   execute_process(COMMAND ${CMAKE_COMMAND} --build . --target cppunit --config Release
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/cppunit-src )
 
   add_subdirectory(${CMAKE_BINARY_DIR}/cppunit-src ${CMAKE_BINARY_DIR}/cppunit-build)

endif(NOT CPPUNIT_FOUND)


# compile test cases
include( FindCPPUNIT )

if( CPPUNIT_FOUND )

   ## setup
   include(CTest)

   include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../include"
        "${CMAKE_CURRENT_SOURCE_DIR}/cppunit/cppunit_example"
        "${CPPUNIT_INCLUDE_DIR}"
    )
   
   
    
    ## build info 
    MESSAGE( STATUS "CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
    if("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
     MESSAGE( STATUS "Visual Studio 64bit compiler: ${CMAKE_CL_64}")
    endif()
    MESSAGE( STATUS "Generated with config types : ${CMAKE_CONFIGURATION_TYPES}")
    MESSAGE( STATUS "                 Build Type : ${CMAKE_BUILD_TYPE}" )
    MESSAGE( STATUS "            CppUnit library : ${CPPUNIT_LIBRARIES}" )
    MESSAGE( STATUS "      CppUnit Debug library : ${CPPUNIT_DEBUG_LIBRARY}" )
    MESSAGE( STATUS "         Cpp compiler flags : ${CMAKE_CXX_FLAGS}" )
    


    
    ## add test cases

    add_executable( Test_cppunit Test_cppunit.cpp ${CMAKE_CURRENT_SOURCE_DIR}/cppunit/cppunit_example/Money.cpp  )
    target_link_libraries( Test_cppunit optimized ${CPPUNIT_LIBRARY} debug ${CPPUNIT_DEBUG_LIBRARY} )
    add_test( NAME Test_cppunit COMMAND Test_cppunit WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} )
    #add_custom_command( TARGET Test_cppunit POST_BUILD COMMAND Test_cppunit )

     ## fasta reader test cases
      
     add_executable( Test_fastareader test_fastareader.cpp ${CMAKE_SOURCE_DIR}/src/FastaReader.cpp ${CMAKE_SOURCE_DIR}/src/Utils.cpp  )
     target_link_libraries( Test_fastareader optimized FastaReader Utils ${CPPUNIT_LIBRARY} debug FastaReader Utils ${CPPUNIT_DEBUG_LIBRARY} )
     add_test( NAME Test_fastareader COMMAND Test_fastareader WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} )

     add_executable( Test_utils test_utils.cpp ${CMAKE_SOURCE_DIR}/src/Utils.cpp  )
     target_link_libraries( Test_utils optimized Utils ${CPPUNIT_LIBRARY} debug Utils ${CPPUNIT_DEBUG_LIBRARY} )
     add_test( NAME Test_utils COMMAND Test_utils WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} )

else( CPPUNIT_FOUND )
   MESSAGE(SEND_ERROR "Could not find CppUnit library ...")
endif( CPPUNIT_FOUND )

