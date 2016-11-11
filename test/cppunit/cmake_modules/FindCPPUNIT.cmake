#
# Adapted from : https://github.com/phtrivier/cppunit-money-example-cmake/blob/master/code/cmake_modules/FindCPPUNIT.cmake
#
# Find the CppUnit includes and library
#
# This module defines
# CPPUNIT_INCLUDE_DIR, where to find tiff.h, etc.
# CPPUNIT_LIBRARIES, the libraries to link against to use CppUnit.
# CPPUNIT_FOUND, If false, do not try to use CppUnit.

# also defined, but not for general use are
# CPPUNIT_LIBRARY, where to find the CppUnit library.
# CPPUNIT_DEBUG_LIBRARY, where to find the CppUnit library in debug
# mode.

SET(CPPUNIT_FOUND "NO")

FIND_PATH(CPPUNIT_INCLUDE_DIR
	cppunit/TestCase.h
	PATHS
		cppunit/include
		/usr/local/include
		/usr/include
		${CMAKE_BINARY_DIR}/cppunit-src/include
		${CMAKE_BINARY_DIR}/cppunit-build/include/cppunit
)

# With Win32, important to have both
IF(${CMAKE_GENERATOR} MATCHES "Visual Studio")
  FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib
	       ${CMAKE_BINARY_DIR}/cppunit-src/lib/Release)
	       
  FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY cppunitd
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib
	       ${CMAKE_BINARY_DIR}/cppunit-src/lib/Debug)
ELSE(${CMAKE_GENERATOR} MATCHES "Visual Studio")
  # On unix system, debug and release have the same name
  FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib
	       ${CMAKE_BINARY_DIR}/cppunit-src/lib)
	       
  FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY cppunit
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib
	       ${CMAKE_BINARY_DIR}/cppunit-src/lib)

ENDIF(${CMAKE_GENERATOR} MATCHES "Visual Studio")

IF(CPPUNIT_INCLUDE_DIR)
  IF(CPPUNIT_LIBRARY)
    SET(CPPUNIT_FOUND "YES")
    SET(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} ${CMAKE_DL_LIBS})
    SET(CPPUNIT_DEBUG_LIBRARIES ${CPPUNIT_DEBUG_LIBRARY} ${CMAKE_DL_LIBS})
  ELSE (CPPUNIT_LIBRARY)
    IF (CPPUNIT_FIND_REQUIRED)
      MESSAGE(WARNING "Could not find library CppUnit.")
    ENDIF (CPPUNIT_FIND_REQUIRED)
  ENDIF(CPPUNIT_LIBRARY)
ELSE(CPPUNIT_INCLUDE_DIR)
  IF (CPPUNIT_FIND_REQUIRED)
    MESSAGE(WARNING "Could not find library CppUnit.")
  ENDIF(CPPUNIT_FIND_REQUIRED)
ENDIF(CPPUNIT_INCLUDE_DIR)
