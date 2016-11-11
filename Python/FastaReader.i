%module FastaReader

%include "stl.i"
%include "std_string.i"
%include "typemaps.i"

%{

/* define python init method */
#define SWIG_FILE_WITH_INIT

/* Includes the header in the wrapper code */	
#include "FastaReader.hpp"	

%}

/* Parse the header file to generate wrappers */
%include "FastaReader.hpp"

