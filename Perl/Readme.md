# Perl example

- [ Build swig perl modules with cmake, see swig_perl.md](swig_perl.md)

---

    perl fasta_stats.pl -f ../test/data/masked.fa
    
    seq_id	seq_num	length bp	unmasked bp	masked bp	% masked
    0	r1	0	0	0	0
    nN-*	r2	4	3	1	25
    0masked	r3	10	10	0	0
    5masked	r4	10	5	5	50
