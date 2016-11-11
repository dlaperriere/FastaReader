# DESCRIPTION
#
# Calculate masked/unmasked bp stats
#
# USAGE:
#         perl fasta_stats.pl -fasta=name
#
use strict;
use warnings;

use File::Basename;
use FindBin qw($Bin);
use lib "$Bin";
use Getopt::Long;

use FastaReader;


my $AUTHOR = "David Laperriere";
my $LAST_CHANGED = "2016/11/03";

#################################################################
# METHODS

## Display message explaining how to use the script & exit
sub usage($)
{
  my ($msg) = @_;
  my $script =  basename($0);

print STDERR <<END;
Calculate masked/unmasked bp stats

Usage:
   perl $script -fasta=filename 

 $AUTHOR $LAST_CHANGED 
 ------------------------------------------- 
 $msg 

END
exit(0);
} #/ usage

#################################################################
# Check parameters
my ($fasta_file);

GetOptions (
            "help|?"   => sub { usage("") },
            "fasta_file=s"  => \$fasta_file,
           );

&usage("must provide a fasta file name...") unless $fasta_file;
&usage("Could not read fasta file \'$fasta_file\' : $! ...") unless -f $fasta_file;

#################################################################
# MAIN

my $fr = new FastaReader::FastaReader($fasta_file);
my $seq_count = 0;

print STDOUT join("\t","seq_id","seq_num","length bp","unmasked bp","masked bp","% masked")."\n";

while($fr->hasNextSequence())
{
    $seq_count++;
    $fr->readSequence();
    my $slength = $fr->SequenceLength();
    my $seq = $fr->Sequence();
    my$seq_id = $fr->Id();
    my $seq_num = "r".$seq_count;

    my $seq_masked = $seq;
    $seq_masked =~ s/[A-Z]|\-|\*//g;
    my $mlength = length($seq_masked);
    my $percent = 0;
    $percent = 100*($mlength/$slength) if $slength >0;
    
   print STDOUT join("\t",$seq_id,$seq_num,$slength,$slength-$mlength,$mlength,$percent)."\n";
    
}

exit(0);


