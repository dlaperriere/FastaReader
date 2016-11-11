#!/usr/bin/env python
"""
 DESCRIPTION

 Calculate masked/unmasked bp stats

 USAGE:
        python fasta_stats.py -fasta=name
"""
from __future__ import print_function

import argparse
import os
import re
import sys
import textwrap

import FastaReader


AUTHOR = "David Laperriere"
LAST_CHANGED = "2016/11/03"

#################################################################
# METHODS

__version_info__ = (1, "1b")
__version__ = '.'.join(map(str, __version_info__))
__author__ = "David Laperriere dlaperriere@outlook.com"


def usage(msg):
    """ Display message explaining how to use the script & exit """
    script = __file__

    usage_text  = """
   Calculate masked/unmasked bp stats

  Usage:
     python fasta_stats.py-fasta=filename 

   {author} {last_change} 
   ------------------------------------------- 
   {msg} 
  """
    text = textwrap.dedent(usage_text).strip()
    print(text.format(author=AUTHOR, last_change=LAST_CHANGED, msg=msg, file=sys.stderr))
    exit(0)


def build_argparser():
    """ Build command line arguments parser """
    parser = argparse.ArgumentParser(
        prog=__file__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description=textwrap.dedent('''
      Calculate masked/unmasked bp stats
                               '''),
        epilog=textwrap.dedent('''
    Example

       python fasta_stats.py -fasta=name

        ''')
    )
    parser.add_argument('-f', '--fasta',
                        type=str,
                        required=True,
                        default=None,
                        help='fasta filename')

    parser.add_argument('-v', '--version', action='version',
                        version="%(prog)s v" + __version__)

    return parser


#################################################################
# MAIN
def main():
    """ Main: parse arguments and calculate masked/unmasked bp stats"""

    # Check parameters
    fasta_file = "?"
    parser = build_argparser()
    pyargs = parser.parse_args()
    if(pyargs.fasta):
        fasta_file = pyargs.fasta
    else:
        usage("must provide a fasta file name...")

    if(not os.path.isfile(fasta_file)):
        usage("Could not read fasta file \'fasta_file\' : ! ...")

    fr = FastaReader.FastaReader(fasta_file)
    seq_count = 0

    print("\t".join(("seq_id", "seq_num", "length bp",
                     "unmasked bp", "masked bp", "% masked")))

    while(fr.hasNextSequence()):
        seq_count += 1
        fr.readSequence()
        seq = fr.Sequence()
        seq_id = fr.Id()
        seq_num = "r" + str(seq_count)

        seq_masked = seq
        seq_masked = re.sub("[A-Z]|\-|\*", "", seq_masked)
        slength = len(seq)
        mlength = len(seq_masked)
        #print (" <--> ".join((seq,seq_masked)))
        percent = 0
        if slength > 0:
            percent = 100 * mlength / slength
        print("\t".join((seq_id, seq_num, str(slength), str(
            slength - mlength), str(mlength), str(int(percent)))))
    exit(0)

if __name__ == "__main__":
    main()
    exit(0)
