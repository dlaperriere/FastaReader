
#include <map>

#include "FastaReader.hpp"
#include "Utils.hpp"

#include "count_fasta.hpp"

//  count - Print nucleotide count (A,C,G,T, N)
void count(std::string fasta_file)
{
    Utils utils;
    //std::cerr<< "Stats     Fasta file :\'"<< fasta_file <<"\'" << std::endl;

    FastaReader fr(fasta_file);
    size_t seq_num = 0;
    std::vector<std::string> header = {"seq_id","A","C","G","T","N","Other"};
    std::cout << utils.join(header,'\t') << std::endl;

    while (fr.hasNextSequence()  ) {
        fr.readSequence();
        seq_num++;
        auto seq_id = fr.Id();
        auto seq = fr.Sequence();

        map<char,int> nucleotide_count = {{'A', 0 }, {'C', 0 }, {'G', 0 }, {'T', 0 }, {'N', 0 }, {'?', 0 } };

        // count nucleotides ACGTN  or other
        auto slength = seq.length();
        for(size_t i = 0; i<slength; i++) {
            char nuc = std::toupper(seq[i]);

            switch(nuc) {
            case 'A':
                nucleotide_count['A'] += 1;
                break;
            case 'C':
                nucleotide_count['C'] += 1;
                break;
            case 'G':
                nucleotide_count['G'] += 1;
                break;
            case 'T':
                nucleotide_count['T'] += 1;
                break;
            case 'X':
            case 'N':
                nucleotide_count['N'] += 1;
                break;
            default:
                nucleotide_count['?'] += 1;
                break;
            }
        }

        std::vector<std::string> seq_stats = {seq_id, std::to_string(nucleotide_count['A']), std::to_string(nucleotide_count['C']), std::to_string(nucleotide_count['G']), std::to_string(nucleotide_count['T']), std::to_string(nucleotide_count['N']), std::to_string(nucleotide_count['?'])};
        std::cout << utils.join(seq_stats,'\t') << std::endl;

    }

}

