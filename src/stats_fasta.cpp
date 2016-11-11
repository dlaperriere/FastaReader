
#include "FastaReader.hpp"
#include "Utils.hpp"
#include <regex>    // require c++11 compiler support

#include "stats_fasta.hpp"

// stats - Print sequence stats
void stats(std::string fasta_file)
{
    Utils utils;

    FastaReader fr(fasta_file);
    size_t seq_num = 0;
    std::vector<std::string> header = {"seq_id","seq_num","length bp","unmasked bp","masked bp","% masked"};
    std::cout << utils.join(header,'\t') << std::endl;
    while (fr.hasNextSequence()  ) {
        fr.readSequence();
        seq_num++;

        auto seq_id = fr.Id();
        auto seq = fr.Sequence();

        std::regex not_masked("[A-Z\\-\\*]");
        std::stringstream result;
        std::regex_replace(std::ostream_iterator<char>(result), seq.begin(), seq.end(),not_masked,"");
        auto mseq = result.str();
        //std::cout << seq_id << "\t" << seq << " <--> " << mseq << std::endl;

        auto slength = seq.length();
        auto mlength = mseq.length();

        size_t percent  = 0;
        if(slength >0) {
            percent = (100*mlength)/slength;
        }

        std::vector<std::string> seq_stats = {seq_id,"r"+std::to_string(seq_num),std::to_string(slength),std::to_string(slength-mlength),std::to_string(mlength),std::to_string(percent)};
        std::cout << utils.join(seq_stats,'\t') << std::endl;

    }

}

