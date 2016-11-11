@echo on

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

mkdir src
mkdir src/main
mkdir src/main/java
mkdir src/main/java/com
mkdir src/main/java/com/github
mkdir src/main/java/com/github/dlaperriere
copy /y Fasta*.java src\main\java\com\github\dlaperriere\
copy /y SWIG*.java src\main\java\com\github\dlaperriere\

copy /y t.fa src\test\resources\t.fa
copy /y src\test\resources\t.fa build\classes\test


del  Fasta*.java
del  SWIG*.java 

javac *.java
javac com\github\dlaperriere\*.java
java -cp .;%CD% example
 

echo gradle build and test
rmdir /S /Q build
call gradle clean
call gradle test
call gradle run
rem java -cp .;%CD% -jar build\libs\FastaTools-all-1.0.jar -h
java -jar build\libs\FastaTools-all-1.0.jar -c stats -f ..\test\data\masked.fa

cd %start_dir%


