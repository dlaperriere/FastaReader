@echo off

rem TDM-GCC-64 5.1 & Active State perl 5.24 64-bit
set PATH=%PATH%;C:\TDM-GCC-64\bin;C:\Perl64\bin;

set build_dir=%cd%\build
rmdir /S /Q %build_dir%\
mkdir %build_dir%
cd %build_dir%

cmake -G "MinGW Makefiles" -DUNIT_TEST=ON -DSWIG_PERL=ON .. 
cmake --build .
ctest

copy /y lib\libPerlFastaReader.dll ..\Perl\FastaReader.dll
perl ..\Perl\fasta_stats.pl -f ..\test\data\masked.fa

