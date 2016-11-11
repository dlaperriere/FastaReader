#!/bin/bash

set -e
set -o pipefail

start_dir=$PWD
build_dir="./build"


# unit test
if [[ -d "$build_dir" ]]; then
    rm -rf $build_dir
fi

mkdir $build_dir
cd $build_dir
cmake  ..
make clean
make
ctest
cd ..

# perl
bash Jenkins/build_perl.sh
cd $start_dir

# python
bash Jenkins/build_python.sh
cd $start_dir

#java
bash Jenkins/build_java.sh
cd $start_dir

