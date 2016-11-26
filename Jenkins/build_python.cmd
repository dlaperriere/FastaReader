@echo off

rem Visual Studio 14 2015 Win64
call "%VS140COMNTOOLS%"vsvars32.bat 
call "%VCINSTALLDIR%"vcvarsall.bat amd64 

set build_dir=%cd%\build
rmdir /S /Q %build_dir%\
mkdir %build_dir%
cd %build_dir%

 cmake -G "Visual Studio 14 2015 Win64"  -DUNIT_TEST=OFF -DSWIG_PYTHON=ON -DPYTHON_LIBRARY=c:\Python27\libs\python27.lib -DPYTHON_EXECUTABLE=C:\Python27\python.exe ..
 cmake --build . --config Release -- /m:2

 copy /y lib\Release\_PythonFastaReader.pyd ..\Python\_FastaReader.pyd
 python2 ..\Python\fasta_stats.py  -f ..\test\data\masked.fa

