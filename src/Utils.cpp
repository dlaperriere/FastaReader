#include "Utils.hpp"

/**
 * Misc. utility methods
 *
 * @author David Laperriere dlaperriere@outlook.com
 * @version  1.0h
 */

using namespace std;

//Check if a string is a file or directory
bool Utils::exists(const std::string& s)
{
    bool file_exists = false;
    if(s.length() > 0) {
        struct stat status;
        int result = stat( s.c_str(), &status );
        if(result == 0) {
            file_exists = true;
        }
    }
    return file_exists;
}


// check if a string is a directory
bool Utils::is_directory(const std::string& path)
{
    bool isdir = false;
    struct stat status;
    // visual studion use _S_IFDIR instead of S_IFDIR
    // http://msdn.microsoft.com/en-us/library/14h5k7ff.aspx
#ifdef _MSC_VER
#define S_IFDIR _S_IFDIR
#endif
    stat( path.c_str(), &status );
    if ( status.st_mode &  S_IFDIR  ) {
        isdir = true;
    }
// #endif
    return isdir;
}

// Remove non alphabetic characters from a string
std::string Utils::str_keep_alpha(const std::string& s)
{
    std::string new_str;
    for(std::size_t it =0; it < s.size(); it++) {
        if( std::isalpha(s[it]) ) {
            new_str += s[it];
        }
    }
    return new_str;
}


// Remove invalid sequence characters from a string
std::string Utils::str_keep_valid_sequence(const std::string& s)
{
    std::string new_str;
    for(std::size_t it =0; it < s.size(); it++) {
        if( std::isalpha(s[it]) || s[it] == '-' || s[it] == '*' ) {
            new_str += s[it];
        }
    }
    return new_str;
}



// Replace char in a string
std::string Utils::str_replace_char(const std::string& s,char o,char r)
{
    std::string new_str(s);
    for(std::size_t it =0; it < new_str.size(); it++) {
        if(new_str[it] == o) {
            new_str[it] = r;
        }
    }
    return new_str;
}

//Convert a string to a double
double Utils::str2double(const std::string& s)
{
    char *pEnd;
    double d = strtod( s.c_str(), &pEnd );
    // error checking
    errno = 0;
    std::string error_msg;
    if (pEnd == s.c_str()) {
        /* no conversion at all */
        error_msg = "  could not convert \'";
        error_msg.append(s);
        error_msg.append("\' to a number...");
        throw std::invalid_argument(error_msg);
    } else if (*pEnd != '\0') {
        /* incomplete conversion */
        error_msg = "  incomplete convertion \'";
        error_msg.append(s);
        error_msg.append("\' to a number...");
        throw std::invalid_argument(error_msg);
    } else if (errno == ERANGE) {
        /* out of  range */
        error_msg = "  out of range error while converting \'";
        error_msg.append(s);
        error_msg.append("\' to a number...");
        throw std::invalid_argument(error_msg);
    }
    return d;
}


// string to UPPERCASE string
std::string Utils::str2uppercase(const std::string& s)
{
    std::string UPPER(s);
    for (std::size_t i = 0; i < s.length(); i++) {
        UPPER[i] = (char)std::toupper(s[i]) ;
    }
    return  UPPER;
}


// join vector of string
// based on https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s09.html
std::string Utils::join(const std::vector<std::string>& vstrings, char delim)
{
    std::string delim_str(1,delim);
    return join(vstrings,delim_str);
}

// join vector of string
std::string Utils::join(const std::vector<std::string>& vstrings, std::string& delim)
{
    std::string joined = "";
    for (auto p = vstrings.begin(); p != vstrings.end(); ++p) {
        joined += *p;
        if (p != vstrings.end() - 1)
            joined += delim;
    }
    return joined;
}

// split string
// based on http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> Utils::split(const std::string& str, char delim )
{
    std::string delim_str(1,delim);
    return split(str,delim_str);
}

// split string
std::vector<std::string> Utils::split(const std::string& str, std::string& delim )
{
    std::vector<std::string> splitstr;
    std::size_t start = 0, end = 0;
    while((end = str.find(delim, start)) != std::string::npos) {
        splitstr.push_back(str.substr(start, end - start));
        start = end+1;
    }
    splitstr.push_back(str.substr(start));

    return splitstr;
}


