
## Generate SWIG Perl bindings

### Windows

#### Build with TDM-GCC-64 5.1 & Active State perl 5.24 64-bit


    set PATH=%PATH%;C:\TDM-GCC-64\bin;C:\Perl64\bin;
    
    mkdir build
    cd build
    
    cmake -G "MinGW Makefiles" -DSWIG_PERL=ON .. 
    cmake --build .
    ctest
    
    #Test project C:/Repos/fastareader-dev/build
    #    Start 1: Test_cppunit
    #1/3 Test #1: Test_cppunit .....................   Passed    0.12 sec
    #    Start 2: Test_fastareader
    #2/3 Test #2: Test_fastareader .................   Passed    0.10 sec
    #    Start 3: Test_utils
    #3/3 Test #3: Test_utils .......................   Passed    0.08 sec
    #
    #100% tests passed, 0 tests failed out of 3
    #
    #Total Test time (real) =   0.34 sec
    
    copy /y lib\libPerlFastaReader.dll ..\Perl\FastaReader.dll
    perl ..\Perl\fasta_stats.pl -f ..\test\data\masked.fa

    # seq_id   seq_num length bp unmasked bp masked bp % masked
    # 0	       r1      0         0           0         0
    # nN-*     r2      4         3           1         25
    # 0masked  r3      10        10          0         0
    # 5masked  r4      10        5           5         50



- http://tdm-gcc.tdragon.net/download
- http://www.activestate.com/activeperl/downloads


### Linux

    mkdir build
    cd build
    cmake -DSWIG_PERL=ON -DCMAKE_CXX_FLAGS=-fPIC ..
    
    make clean
    make
    cd ..
    
    cp build/lib/libPerlFastaReader.so Perl/libFastaReader.so
    perl Perl/fasta_stats.pl -f test/data/masked.fa
 

