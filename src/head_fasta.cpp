
#include "FastaReader.hpp"
#include <string>

#include "head_fasta.hpp"

// head - Print the first n sequences of a fasta file
void head(std::string fasta_file, int num)
{

    FastaReader fr(fasta_file);
    int records_seen = 0;

    while (fr.hasNextSequence() && num >= 0  ) {

        fr.readSequence();

        std::cout << ">" << fr.Id() << " " << fr.Description() << std::endl;
        std::cout <<  fr.Sequence() << std::endl;

        records_seen++;
        if(records_seen >= num) {
            break;
        }
    }

}

