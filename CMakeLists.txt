cmake_minimum_required(VERSION 3.3)

project(FastaReader CXX)

set(CMAKE_CXX_STANDARD 11)

# The project version number.
set(VERSION_MAJOR   2016  CACHE STRING "Project major version number.")
set(VERSION_MINOR   001   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   a   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

## project dirs

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories( "${CMAKE_SOURCE_DIR}/include" )
add_subdirectory ( "${CMAKE_SOURCE_DIR}/src" )

## programs

  add_executable (fastatools  ${CMAKE_SOURCE_DIR}/src/fastatools.cpp  ${CMAKE_SOURCE_DIR}/src/FastaReader.cpp ${CMAKE_SOURCE_DIR}/src/Utils.cpp ${CMAKE_SOURCE_DIR}/src/count_fasta.cpp ${CMAKE_SOURCE_DIR}/src/head_fasta.cpp ${CMAKE_SOURCE_DIR}/src/stats_fasta.cpp)
  target_link_libraries( fastatools optimized FastaReader Utils debug FastaReader Utils )


## tests
option (UNIT_TEST "Build unit tests" ON)

if (UNIT_TEST)
  enable_testing ()
  add_subdirectory ( "${CMAKE_SOURCE_DIR}/test" )
else()
  message("Skip unit tests...")
endif()

## Documentation

find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message( "Doxygen is needed to build the documentation.")
    else()

      set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doc/Config/Doxyfile.in)
      set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doc/Config/Doxyfile)

      configure_file(${doxyfile_in} ${doxyfile} @ONLY)

      add_custom_target(doc ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen"
         VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Doc/html DESTINATION ${PROJECT_SOURCE_DIR}/doc)
    
    endif()    
    
endif()

## java bindings
option (SWIG_JAVA "Generate SWIG java bindings" OFF)

if (SWIG_JAVA)
  add_subdirectory ( "${CMAKE_SOURCE_DIR}/Java" )
else()
  message("Skip java bindings...")  
endif()


## perl bindings
option (SWIG_PERL "Generate SWIG perl bindings" OFF)

if (SWIG_PERL)
  add_subdirectory ( "${CMAKE_SOURCE_DIR}/Perl" )
else()
  message("Skip perl bindings...")  
endif()

## python bindings
option (SWIG_PYTHON "Generate SWIG python bindings" OFF)

if (SWIG_PYTHON)
  add_subdirectory ( "${CMAKE_SOURCE_DIR}/Python" )
else()
  message("Skip python bindings...")  
endif()
