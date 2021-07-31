#!/bin/env bash

cd /src

echo Java tests  
bash Jenkins/build_java.sh 

echo Perl tests
bash Jenkins/build_perl.sh  

echo Python tests
bash Jenkins/build_python.sh  
 
#bash Jenkins/build_test.sh
