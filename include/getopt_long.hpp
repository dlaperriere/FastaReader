#ifndef _GETOPT_LONG_HPP_
#define _GETOPT_LONG_HPP_

// getopt_long command line parser
#ifdef _MSC_VER

#include "wgetopt.h"   /* windows version of getopt_long */

#else

#include <getopt.h>    /* for getopt_long; POSIX standard getopt is in unistd.h */

#endif

#endif //_GETOPT_LONG_HPP_
