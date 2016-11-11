
## Generate SWIG Python bindings

### Windows

#### Build with Visual Studio 2015  and Python 2.7

     call "%VS140COMNTOOLS%"vsvars32.bat 
     call "%VCINSTALLDIR%"vcvarsall.bat amd64 
     
     mkdir build
     cd build
     
     cmake -G "Visual Studio 14 2015 Win64"  -DSWIG_PYTHON=ON -DPYTHON_LIBRARY=c:\Python27\libs\python27.lib -DPYTHON_EXECUTABLE=C:\Python27\python.exe ..
     cmake --build . --config Release
     
     copy /y lib\Release\_PythonFastaReader.pyd ..\Python\_FastaReader.pyd
     
     python2 ..\Python\fasta_stats.py  -f ..\test\data\masked.fa
     
    # seq_id   seq_num length bp unmasked bp masked bp % masked
    # 0	       r1      0         0           0         0
    # nN-*     r2      4         3           1         25
    # 0masked  r3      10        10          0         0
    # 5masked  r4      10        5           5         50


### Linux

    mkdir build
    cd build
    cmake -DSWIG_PYTHON=ON -DCMAKE_CXX_FLAGS=-fPIC -DPYTHON_EXECUTABLE=/usr/bin/python3 ..
    
    make clean
    make
    cd ..
    
    cp build/lib/_PythonFastaReader.so Python/_FastaReader.so
    python3 Python/fasta_stats.py -f test/data/masked.fa
