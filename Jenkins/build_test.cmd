@echo off

set start_dir=%cd%
set build_dir=%cd%\build

rmdir /S /Q %build_dir%\

mkdir build
cd build
cmake ..
cmake --build . --config Release -- /m:2
copy /Y cppunit-src\bin\Release\cppunit.dll ..\test\
copy /Y bin\Release\*.exe ..\test\
cd ..

cd test
Test_cppunit
Test_fastareader
Test_utils
