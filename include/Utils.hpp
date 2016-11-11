#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cerrno>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

#include <sys/stat.h> // is_directory

using namespace std;


#ifdef _MSC_VER
#pragma setlocale("C")
#undef _UNICODE
#undef _MBCS
#endif

/**
 * @brief Misc. utility methods.
 *
 * @author David Laperriere dlaperriere@outlook.com
 * @version 1.0g
 *
 */
class Utils
{

public:

    /**
     * Check if a string is a file or directory
     *
     * @param s string file/dir name
     * @return true if it exists
     *
     */

    bool exists(const std::string& s);

    /**
     * Check if a string is a directory
     *
     * @param path string to test
     * @return true if path is a directory, false otherwise
     */
    bool is_directory(const std::string& path);

    /**
     * Remove non alphabetic characters from a string
     *
     * @param s string
     * @return version of the string with only alphabetic characters (a-Z)
     *
     */
    std::string str_keep_alpha(const std::string& s);

    /**
     * Keep only valid sequence code from a string (Nucleic Acid and Amino Acid)
     * http://blast.ncbi.nlm.nih.gov/blastcgihelp.shtml
     *
     * @param s string
     * @return version of the string with valid characters (a-Z - and *)
     *
     */
    std::string str_keep_valid_sequence(const std::string& s);


    /**
     * Replace char in a string
     *
     * @param s string
     * @param o original char
     * @param r replacement char
     * @return version of the string with replaced char
     *
     */
    std::string str_replace_char(const std::string& s,char o,char r);


    /**
     * Convert a string to a double
     *
     * @param s string
     * @return double version of the string
     *
     * @throw  std::invalid_argument in case of error during the convertion
     */
    double str2double(const std::string& s);


    /**
     * Convert a string to UPPERCASE string
     *
     * @param s string to uppercase
     * @return uppercase version of the string
     */
    std::string str2uppercase(const std::string& s);

    /**
     * Join a vector of string
     *
     * @param vstrings vector of string to join
     * @param delim char to insert between strings
     * @return string with the vector strings seperated by the delimiter
     */
    std::string join(const std::vector<std::string>& vstrings, char delim);

    /**
     * Join a vector of string
     *
     * @param vstrings vector of string to join
     * @param delim string to insert between strings
     * @return string with the vector strings seperated by the delimiter
     */
    std::string join(const std::vector<std::string>& vstrings, std::string&delim);

    /**
      * Split a string
      *
      * @param str string to split
      * @param delim char used to split the string
      * @return vector with the strings that were seperated by the delimiter
      */
    std::vector<std::string> split(const std::string& str, char delim );

    /**
        * Split a string
        *
        * @param str string to split
        * @param delim string used to split the string
        * @return vector with the strings that were seperated by the delimiter
        */
    std::vector<std::string> split(const std::string& str, std::string& delim );

};

#endif //_UTILS_HPP_

