## C++ Fasta file reader

### Usage
 
    #include "FastaReader.hpp" 
    
    FastaReader fr("file.fasta"); 
    while(fr.hasNextSequence()) 
    { 
       fr.readSequence();
       std::string seq = fr.Sequence();         
       // sequence manipulation 
    }

 Sequences (fasta record) are read one at a time to limit memory usage. Non alphabetical characters present in the sequences are ignored (e.g space , tabs, ...) .

### Fasta file format


    >id description
    ACGTN
    >id description
    ACCCC


 - https://en.wikipedia.org/wiki/FASTA_format
 
 
## Fasta command line utilities

    # bin/fastatools.exe -h
    
     fastatools - fasta file utilities
     ----------------------------------
     USAGE:
     
     count - Print nucleotide count (A,C,G,T,N):
        fastatools -c count -f sequence.fa
 
     head  - Print the first n sequences of a fasta file:
        fastatools -c head  -f sequence.fa  -n number_of_sequence_to_print
	
     stats - Print sequence stats (# bp, % masked):
        fastatools -c stats -f sequence.fa

 
## Build with cmake  

    
### Visual Studio

    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release
    
    copy /Y cppunit-src\bin\Release\cppunit.dll ..\test\
    copy /Y bin\Release\*.exe ..\test\
    
    cd ..
   
    cd test
    Test_cppunit
    Test_fastareader
    Test_utils 
   
    #...
    Unit test for FastaReader class
    =========================
    FastaReaderTestCase::fastafile : OK
    FastaReaderTestCase::fastafile_donotexist : OK
    FastaReaderTestCase::fastafile_directory : OK
    =========================


### Linux

    mkdir build
    cd build
    cmake ..
    make
    
    ctest
    
     Test project /home/jenkins/workspace/FastaReader/build
         Start 1: Test_cppunit
     1/3 Test #1: Test_cppunit .....................   Passed    0.00 sec
         Start 2: Test_fastareader
     2/3 Test #2: Test_fastareader .................   Passed    0.00 sec
         Start 3: Test_utils
     3/3 Test #3: Test_utils .......................   Passed    0.00 sec

## Generate Perl, Python or Java bindings with SWIG 
 

### perl
     cmake .. -DSWIG_PERL=ON
     cmake .. -DSWIG_PERL=ON -DPERL_EXECUTABLE=/path/perl -DSWIG_EXECUTABLE=/path/swig

- [See Perl/swig_perl.md](Perl/swig_perl.md)

### python
     cmake .. -DSWIG_PYTHON=ON

- [See Python/swig_python.md](Python/swig_python.md)

### java
     cmake .. -DSWIG_JAVA=ON

- [See Java/swig_java.md](Java/swig_java.md)



### Limitation

The maximum size of a sequence is the  size of a std::string (std::size_t) .

     
### Author
David Laperriere dlaperriere@outlook.com



