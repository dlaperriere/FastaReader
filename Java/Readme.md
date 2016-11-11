# Java example

- [ Build swig java classes with cmake, see swig_java.md](swig_java.md)

## Windows

    mkdir com
    mkdir com\github
    mkdir com\github\dlaperriere
    
    copy /y Fasta*.java com\github\dlaperriere\
    copy /y SWIG*.java com\github\dlaperriere\
    
    copy /y Fasta*.java src\main\java\com\github\dlaperriere\
    copy /y SWIG*.java src\main\java\com\github\dlaperriere\
    
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


## Linux


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
     
    # * creating FastaReader
    # * reading sequences
    #    sequence 1 :            2       aa
    #    sequence 2 :            3       gcc
    #    sequence 3 :            4       AcGg
    #    sequence 4 :            15      AcgtNn*--TGCaxX
    #    sequence empty :                0