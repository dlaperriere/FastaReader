%module FastaReader

%include "stl.i"
%include "std_string.i"
%include "typemaps.i"

%{
/* Includes the header in the wrapper code */	
#include "FastaReader.hpp"	

%}

/* Parse the header file to generate wrappers */
%include "FastaReader.hpp"

