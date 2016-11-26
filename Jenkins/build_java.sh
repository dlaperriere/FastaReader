#!/bin/bash


start_dir=$PWD
build_dir="./build"

if [[ -d "$build_dir" ]]; then
    rm -rf $build_dir
fi

echo --------------------------------
echo generate SWIG java bindings
mkdir $build_dir
cd $build_dir

cmake  -DUNIT_TEST=OFF -DSWIG_JAVA=ON -DCMAKE_CXX_FLAGS=-fPIC ..
make clean
make -j 2
cp lib/libFastaReaderJAVA.so ../Java/libFastaReader.so

cd ..

echo --------------------------------
echo run example program
cd Java

mkdir com
mkdir com/github
mkdir com/github/dlaperriere

cp Fasta*.java com/github/dlaperriere/
cp SWIG*.java com/github/dlaperriere/

mkdir src
mkdir src/main
mkdir src/main/java
mkdir src/main/java/com
mkdir src/main/java/com/github
mkdir src/main/java/com/github/dlaperriere
cp Fasta*.java src/main/java/com/github/dlaperriere/
cp SWIG*.java src/main/java/com/github/dlaperriere/

cp t.fa src/test/resources/t.fa
cp src/test/resources/t.fa build/classes/test


rm  Fasta*.java
rm  SWIG*.java 

pwd

javac *.java
javac com/github/dlaperriere/*.java
export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
java -cp .:$PWD example
 
echo --------------------------------
echo gradle build and test
rm -rf $build_dir
gradle clean test run
# java -cp .;%CD% -jar build/libs/FastaTools-all-1.0.jar -h
java -jar build/libs/FastaTools-all-1.0.jar -c stats -f ../test/data/masked.fa


cd $start_dir
