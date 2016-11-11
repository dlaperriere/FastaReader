## Generate SWIG Java bindings

### Windows

#### Build with Visual Studio 2015

    rem Visual Studio 14 2015 Win64
    call "%VS140COMNTOOLS%"vsvars32.bat 
    call "%VCINSTALLDIR%"vcvarsall.bat amd64 
    
    set start_dir=%cd%
    set build_dir=%cd%\build
    rmdir /S /Q %build_dir%\
    mkdir %build_dir%
    cd %build_dir%
    
    echo generate SWIG java bindings 
    cmake -G "Visual Studio 14 Win64" -DUNIT_TEST=OFF -DSWIG_JAVA=ON ..
    cmake --build . --config Release
    copy /y lib\Release\FastaReaderJAVA.dll ..\Java\FastaReader.dll
    
    cd ..
    
    echo run example program
    cd Java
    
    mkdir com
    mkdir com\github
    mkdir com\github\dlaperriere
    
    copy /y Fasta*.java com\github\dlaperriere\
    copy /y SWIG*.java com\github\dlaperriere\
    
    copy /y Fasta*.java src\main\java\com\github\dlaperriere\
    copy /y SWIG*.java src\main\java\com\github\dlaperriere\

    copy /y t.fa src\test\resources\t.fa
    copy /y src\test\resources\t.fa build\classes\test
    
    del  Fasta*.java
    del  SWIG*.java 
    
    javac *.java
    javac com\github\dlaperriere\*.java
    java -cp .;%CD% example
    
    # * creating FastaReader
    # * reading sequences
    #    sequence 1 :            2       aa
    #    sequence 2 :            3       gcc
    #    sequence 3 :            4       AcGg
    #    sequence 4 :            15      AcgtNn*--TGCaxX
    #    sequence empty :                0

### Linux

    #!/bin/bash
    start_dir=$PWD
    build_dir="./build"
    if [[ -d "$build_dir" ]]; then
        rm -rf $build_dir
    fi
    
    echo generate SWIG java bindings
    mkdir $build_dir
    cd $build_dir
    cmake  -DUNIT_TEST=OFF -DSWIG_JAVA=ON -DCMAKE_CXX_FLAGS=-fPIC ..
    make clean
    make 
    cp lib/libFastaReaderJAVA.so ../Java/libFastaReader.so
    cd ..
    
    echo run example program
    cd Java
    mkdir com
    mkdir com/github
    mkdir com/github/dlaperriere
    cp Fasta*.java com/github/dlaperriere/
    cp SWIG*.java com/github/dlaperriere/
    cp Fasta*.java src/main/java/com/github/dlaperriere/
    cp SWIG*.java src/main/java/com/github/dlaperriere/
    
    rm  Fasta*.java
    rm  SWIG*.java 

    javac *.java
    javac com/github/dlaperriere/*.java
    export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
    java -cp .:$PWD example
 
    echo gradle build and test
    rm -rf $build_dir
    gradle clean
    gradle test
    gradle run

    java -jar build/libs/FastaTools-all-1.0.jar -c stats -f ../test/data/masked.fa
    cd $start_dir
    