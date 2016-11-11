/**
 * @brief fastatools - fasta file utilities
 * @author David Laperriere dlaperriere@outlook.com
 * @version 1.0
 *
 *  USAGE:
 *  count - Print nucleotide count (A,C,G,T,N):
 *     fastatools -c count -f sequence.fa
 *
 *  head  - Print the first n sequences of a fasta file:
 *     fastatools -c head  -f sequence.fa  -n number_of_sequence_to_print
 *
 *  stats - Print sequence stats (# bp, % masked):
 *     fastatools -c stats -f sequence.fa
 *
 */

#include <string>


#include "FastaReader.hpp"
#include "Utils.hpp"

#include "count_fasta.hpp"
#include "head_fasta.hpp"
#include "stats_fasta.hpp"

#include "getopt_long.hpp"

/**
 * @brief Print fastatools command line usage info
 */
void usage()
{
    std::cerr<< " fastatools - fasta file utilities"  << std::endl;
    std::cerr<< "----------------------------------" << std::endl;
    std::cerr<<" USAGE:" << std::endl;
    std::cerr<<" count - Print nucleotide count (A,C,G,T,N):" << std::endl;
    std::cerr<<"    fastatools -c count -f sequence.fa  " << std::endl;
    std::cerr<<" head  - Print the first n sequences of a fasta file:" << std::endl;
    std::cerr<<"    fastatools -c head  -f sequence.fa  -n number_of_sequence_to_print" << std::endl;
    std::cerr<<" stats - Print sequence stats (# bp, % masked):" << std::endl;
    std::cerr<<"    fastatools -c stats -f sequence.fa  " << std::endl;
    std::cerr << std::endl;

}

/**
 * @brief Fastatools Main : check  parameters and run command
 */
int main(int argc, char *argv[])
{

    Utils util;
    std::string command_name = "";
    std::string fasta_file = "";
    bool fasta_file_set = false;
    int num = 1;

    // process parameters with getopt_long
    int option_index = 0;

    static struct option long_options[] = {
        {"help",     no_argument,       0, 'h'},
        {"command",     required_argument,       0, 'c'},
        {"fasta",     required_argument,       0, 'f'},
        {"num",    required_argument, 0, 'n'},
        {0, 0, 0, 0}
    };

    int c ;

    while ( (c  = getopt_long (argc, &argv[0], "hc:f:n:",
                               long_options, &option_index) ) != -1) {

        /* Detect the end of the options. */
        if (c == -1) {
            break;
        }

        switch (c) {

        //*1.1 display help message
        case 'h':
            usage();
            exit(0);
            break;

        //*1.2 set command name
        case 'c':
            if (optarg != NULL) {
                command_name = std::string(optarg);
                command_name = util.str_replace_char(command_name,'\a',' ');
            } else {
                command_name = "";
            }
            break;

        //*1.3 set fasta file name
        case 'f':
            if (optarg != NULL) {
                fasta_file = std::string(optarg);
                fasta_file = util.str_replace_char(fasta_file,'\a',' ');
                fasta_file_set = true;
            } else {
                fasta_file = "";
                fasta_file_set = false;
            }
            break;

        //*1.4 number of sequence to print
        case 'n':
            if (optarg != NULL) {
                num = atoi(optarg);
            }
            break;

        case '?':
            std::cerr << argv[0] << ": unknown option \'-" << optopt << "\': ignored...\n";
            break;

        default:
            usage();
            exit(-1);
        }
    }

    // check parameters
    if(!fasta_file_set) {
        usage();
        exit(-1);
    }

    if(!util.exists(fasta_file)) {
        std::cerr<< "   Fasta file \'"<< fasta_file <<"\' does not exist..."<< std::endl;
        exit(-1);
    } else {
        if(util.is_directory(fasta_file)) {
            std::cerr<< "   Fasta file \'"<< fasta_file <<"\' is a directory..."<< std::endl;
            exit(-1);
        }
    }

    if(num < 1) {
        num  = 1;
    }

    // run command
    if( command_name.compare("count") == 0) {
        count(fasta_file);
    } else if( command_name.compare("head") == 0) {
        head(fasta_file,num);
    } else if( command_name.compare("stats") == 0) {
        stats(fasta_file);
    } else {
        std::cerr<< "   unknown command \'"<< command_name <<"\'"<< std::endl;
        usage();
        exit(-1);
    }

    exit(0);
}